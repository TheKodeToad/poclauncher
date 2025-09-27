#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QMessageBox>
#include <QPluginLoader>
#include <QProcessEnvironment>
#include <QStandardPaths>

#include "Application.h"
#include "BuildConfig.h"
#include "PluginLoader.h"
#include "ui/MainWindow.h"
#include "util/MessageBox.h"

using namespace Qt::Literals;

struct Application::Data {
    PluginLoader pluginLoader;
    QIcon logo;
    QString rootPath;
    bool portable = false;
};

Application::Application(int& argc, char** argv) : QApplication(argc, argv), m_data(std::make_unique<Data>()) {}

Application::~Application() {}

PluginLoader& Application::pluginLoader()
{
    return m_data->pluginLoader;
}

const PluginLoader& Application::pluginLoader() const
{
    return m_data->pluginLoader;
}

bool Application::portable() const
{
    return m_data->portable;
}

int Application::run()
{
    setOrganizationDomain(BuildConfig::LAUNCHER_DOMAIN);
    setApplicationName(BuildConfig::LAUNCHER_NAME);
    setApplicationDisplayName(BuildConfig::LAUNCHER_DISPLAYNAME + ' '_L1 + BuildConfig::VERSION_STRING);
    setApplicationVersion(BuildConfig::VERSION_STRING + '\n'_L1 + BuildConfig::GIT_COMMIT);
    setDesktopFileName(BuildConfig::LAUNCHER_APPID);
    setWindowIcon(QIcon(":/icons/logo.svg"_L1));

    QIcon::setThemeSearchPaths(QIcon::themeSearchPaths() << u":/icons"_s);
    QIcon::setThemeName(u"multimc"_s);

    QCommandLineParser parser;

    parser.addOption({ { u"d"_s, u"dir"_s }, u"Use a custom path for launcher data"_s, u"directory"_s });

    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(arguments());

    initDir(parser.value(u"dir"_s));

    (new MainWindow(nullptr))->show();

    return exec();
}

void Application::initDir(const QString& dirParam)
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD)
    m_data->rootPath = QApplication::applicationDirPath() + u"/.."_s;
#elif defined(Q_OS_WIN32)
    m_data->rootPath = QApplication::applicationDirPath();
#elif defined(Q_OS_MAC)
    m_data->rootPath = QApplication::applicationDirPath() + u"/../.."_s;
    // on /macOS, touch the root to force Finder to reload the .app metadata (and fix any icon change issues)
    QFile rootFile(m_rootPath);
    rootFile.setFileTime(QDateTime::currentDateTime(), QFileDevice::FileTime::FileModificationTime);
#endif

    QString specifiedBy;
    QString dataPath;

    static const QString DATA_DIR_ENV = BuildConfig::LAUNCHER_NAME.toUpper() + u"_DATA_DIR"_s;

    if (!dirParam.isEmpty()) {
        specifiedBy = u"command line"_s;
        dataPath = dirParam;
    } else if (QString dataDirEnvValue = QProcessEnvironment::systemEnvironment().value(DATA_DIR_ENV); !dataDirEnvValue.isEmpty()) {
        specifiedBy = u"system environment"_s;
        dataPath = dataDirEnvValue;
    } else {
        // TODO POC: snap support
        // QDir foo;
        // if (DesktopServices::isSnap()) {
        // 	foo = QDir(getenv("SNAP_USER_COMMON"));
        // } else {
        // 	foo = QDir(FS::PathCombine(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation), ".."));
        // }

        dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        specifiedBy = u"persistent data path"_s;

#ifndef Q_OS_MACOS
        if (auto portableUserData = m_data->rootPath + u"/UserData"_s; QDir(portableUserData).exists()) {
            dataPath = portableUserData;
            specifiedBy = u"portable user data path"_s;
            m_data->portable = true;
        } else if (QFile::exists(m_data->rootPath + tr("/portable.txt"))) {
            dataPath = m_data->rootPath;
            specifiedBy = u"portable data path"_s;
            m_data->portable = true;
        }
#endif
    }

    static const QString ERROR_TITLE = tr("Cannot Initialize Data");
    static const QString ERROR_TIP = tr("Make sure you have the required permissions.");

    if (!QDir().exists(dataPath) && !QDir().mkpath(dataPath)) {
        QString message = tr("The launcher data folder could not be created - %1 ('%2')").arg(ERROR_TIP);

        selectableMessageBox(nullptr, tr("Cannot Initialize Data"), message, QMessageBox::Critical)->exec();
        return;
    }
    if (!QDir::setCurrent(dataPath)) {
        QString message = tr("The launcher data folder could not be opened - %1 ('%2')").arg(ERROR_TIP);

        selectableMessageBox(nullptr, tr("Could not set launcher data"), message.arg(dataPath), QMessageBox::Critical)->exec();
        return;
    }

    qDebug() << "Data dir:" << QDir::currentPath() << "- specified by" << specifiedBy;
}
