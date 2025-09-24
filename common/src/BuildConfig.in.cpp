#include "BuildConfig.h"

using namespace Qt::Literals;

namespace BuildConfig {
static QString baseVersionString()
{
    return u"%1.%2.%3"_s.arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);
}

const QString LAUNCHER_NAME = u"@launcher_NAME@"_s;
const QString LAUNCHER_DISPLAYNAME = u"@launcher_DISPLAY_NAME@"_s;
const QString LAUNCHER_APP_BINARY_NAME = u"@PARENT_PROJECT_NAME@"_s;
const QString LAUNCHER_COPYRIGHT = u"launcher_COPYRIGHT"_s;

// clang-format off
const int VERSION_MAJOR = @launcher_VERSION_MAJOR@;
const int VERSION_MINOR = @launcher_VERSION_MINOR@;
const int VERSION_PATCH = @launcher_VERSION_PATCH@;
// clang-format on
const QString VERSION_STRING = baseVersionString() + VERSION_CHANNEL;
const QString VERSION_CHANNEL = u"unknown"_s; // TODO

const QString HELP_URL = u"@launcher_HELP_URL@"_s;
const QString BUG_TRACKER_URL = u"@launcher_BUG_TRACKER_URL@"_s;
const QString TRANSLATIONS_URL = u"@launcher_TRANSLATIONS_URL@"_s;
const QString DISCORD_URL = u"@launcher_DISCORD_URL@"_s;
const QString MATRIX_URL = u"@launcher_MATRIX_URL@"_s;
const QString SUBREDDIT_URL = u"@launcher_SUBREDDIT_URL@"_s;
const QString SOURCE_CODE_URL = u"@launcher_SOURCE_CODE_URL@"_s;

const QString BUILD_DATE = u"@launcher_BUILD_DATE@"_s;
const QString BUILD_PLATFORM = u"@launcher_BUILD_PLATFORM@"_s;
const QString COMPILER_NAME = u"@CMAKE_CXX_COMPILER_ID@"_s;
const QString COMPILER_VERSION = u"@CMAKE_CXX_COMPILER_ID@"_s;
const QString COMPILER_TARGET_SYSTEM = u"@CMAKE_SYSTEM_NAME@"_s;
const QString COMPILER_TARGET_SYSTEM_VERSION = u"@CMAKE_SYSTEM_VERSION@"_s;
const QString COMPILER_TARGET_SYSTEM_PROCESSOR = u"@CMAKE_SYSTEM_PROCESSOR@"_s;

const QString GIT_COMMIT = u"@launcher_GIT_COMMIT@"_s;
const QString GIT_TAG = u"@launcher_GIT_TAG@"_s;
const QString GIT_REFSPEC = u"@launcher_GIT_REFSPEC@"_s;
}  // namespace BuildConfig
