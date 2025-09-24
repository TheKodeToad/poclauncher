#include <QApplication>
#include <QDebug>
#include <QPluginLoader>
#include <QStaticPlugin>
#include <QtPlugin>

#include "common/BuildConfig.h"
#include "core/bootstrap.h"

using namespace Qt::Literals;

Q_IMPORT_PLUGIN(CorePlugin);

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(BuildConfig::LAUNCHER_NAME);
    QApplication::setApplicationDisplayName(BuildConfig::LAUNCHER_DISPLAYNAME + ' '_L1 + BuildConfig::VERSION_STRING);
    QApplication::setDesktopFileName(BuildConfig::LAUNCHER_APP_BINARY_NAME);

    bootstrap();

    return app.exec();
}