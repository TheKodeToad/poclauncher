#pragma once

class QString;

namespace DesktopServices {
/**
 * Open a file with a suitable application.
 * @param path Path of file to open
 * @return true on success
 */
bool openPath(const QString& path);
bool isFlatpak();
bool isSnap();
}  // namespace DesktopServices