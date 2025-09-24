#pragma once

#include <QString>

namespace BuildConfig {
extern const QString LAUNCHER_NAME;
extern const QString LAUNCHER_DISPLAYNAME;
extern const QString LAUNCHER_APP_BINARY_NAME;
extern const QString LAUNCHER_COPYRIGHT;

extern const int VERSION_MAJOR;
extern const int VERSION_MINOR;
extern const int VERSION_PATCH;
extern const QString VERSION_STRING;
extern const QString VERSION_CHANNEL;

extern const QString BUILD_DATE;
extern const QString BUILD_PLATFORM;
extern const QString COMPILER_NAME;
extern const QString COMPILER_VERSION;
extern const QString COMPILER_TARGET_SYSTEM;
extern const QString COMPILER_TARGET_SYSTEM_VERSION;
extern const QString COMPILER_TARGET_PROCESSOR;

extern const QString GIT_COMMIT;
extern const QString GIT_TAG;
extern const QString GIT_REFSPEC;

extern const QString HELP_URL;
extern const QString BUG_TRACKER_URL;
extern const QString TRANSLATIONS_URL;
extern const QString DISCORD_URL;
extern const QString MATRIX_URL;
extern const QString SUBREDDIT_URL;
extern const QString SOURCE_CODE_URL;
}  // namespace BuildConfig
