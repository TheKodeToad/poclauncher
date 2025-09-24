#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QMessageBox>
#include <QPluginLoader>
#include <QProcessEnvironment>
#include <QStandardPaths>

#include "./CorePlugin.h"
#include "common/BuildConfig.h"
#include "common/CustomMessageBox.h"
#include "ui/MainWindow.h"

using namespace Qt::Literals;

void CorePlugin::bootstrap()
{
    QCommandLineParser parser;

    parser.addOption({ { u"d"_s, u"dir"_s }, u"Use a custom path for launcher data"_s, u"directory"_s });

    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(QApplication::arguments());

    initDir(parser.value(u"dir"_s));

    (new MainWindow(nullptr))->show();
}

void CorePlugin::initDir(const QString& dirParam)
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD)
    m_rootPath = QApplication::applicationDirPath() + u"/.."_s;
#elif defined(Q_OS_WIN32)
    m_rootPath = QApplication::applicationDirPath();
#elif defined(Q_OS_MAC)
    m_rootPath = QApplication::applicationDirPath() + u"/../.."_s;
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
        if (auto portableUserData = m_rootPath + u"/UserData"_s; QDir(portableUserData).exists()) {
            dataPath = portableUserData;
            specifiedBy = u"portable user data path"_s;
            m_portable = true;
        } else if (QFile::exists(m_rootPath + tr("/portable.txt"))) {
            dataPath = m_rootPath;
            specifiedBy = u"portable data path"_s;
            m_portable = true;
        }
#endif
    }

    static const QString ERROR_TITLE = tr("Cannot Initialize Data");
    static const QString ERROR_TIP = tr("Make sure you have the required permissions.");

    if (!QDir().exists(dataPath) && !QDir().mkpath(dataPath)) {
        QString message = tr("The launcher data folder could not be created - %1 ('%2')").arg(ERROR_TIP);

        CustomMessageBox::selectable(nullptr, tr("Cannot Initialize Data"), message, QMessageBox::Critical)->exec();
        return;
    }
    if (!QDir::setCurrent(dataPath)) {
        QString message = tr("The launcher data folder could not be opened - %1 ('%2')").arg(ERROR_TIP);

        CustomMessageBox::selectable(nullptr, tr("Could not set launcher data"), message.arg(dataPath), QMessageBox::Critical)->exec();
        return;
    }

    qDebug() << "Data dir:" << QDir::currentPath() << "- specified by" << specifiedBy;
}
