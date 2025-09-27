#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QString>
#include <QUrl>
#include <cstdlib>

#include "util/DesktopServices.h"

using namespace Qt::Literals;

namespace DesktopServices {
bool openPath(const QString& path)
{
    return QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::current().absoluteFilePath(path)));
}

bool isFlatpak()
{
#ifdef Q_OS_LINUX
    static bool result = QFile::exists(u"/.flatpak_info"_s);
    return result;
#else
    return false;
#endif
}

bool isSnap()
{
#ifdef Q_OS_LINUX
    static bool result = getenv("SNAP");
    return result;
#else
    return false;
#endif
}
}  // namespace DesktopServices
