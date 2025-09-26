// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *      Copyright 2013-2021 MultiMC Contributors
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "BuildConfig.h"

#include <QString>

using namespace Qt::Literals;

namespace BuildConfig {
const QString LAUNCHER_NAME = u"@Launcher_NAME@"_s;
const QString LAUNCHER_DISPLAYNAME = u"@Launcher_DISPLAY_NAME@"_s;
const QString LAUNCHER_APP_BINARY_NAME = u"@Launcher_BINARY_NAME@"_s;
const QString LAUNCHER_APPID = u"@Launcher_APP_ID@"_s;
const QString LAUNCHER_COPYRIGHT = u"@Launcher_COPYRIGHT@"_s;
const QString LAUNCHER_DOMAIN = u"@Launcher_DOMAIN@"_s;

const QString GIT_COMMIT = u"@Launcher_GIT_COMMIT@"_s;
const QString GIT_TAG = u"@Launcher_GIT_TAG@"_s;
const QString GIT_REFSPEC = u"@Launcher_GIT_REFSPEC@"_s;

// clang-format off
const int VERSION_MAJOR = @Launcher_VERSION_MAJOR@;
const int VERSION_MINOR = @Launcher_VERSION_MINOR@;
const int VERSION_PATCH = @Launcher_VERSION_PATCH@;
// clang-format on

const QString VERSION_CHANNEL = [] {
    static const QString PREFIX = u"refs/heads/"_s;

    if (GIT_REFSPEC.startsWith(PREFIX))
        return GIT_REFSPEC.mid(PREFIX.length());
    else if (!GIT_COMMIT.isEmpty())
        return GIT_COMMIT.mid(0, 8);
    else
        return GIT_REFSPEC;
}();
const QString VERSION_STRING = [] {
    QString version = u"%1.%2.%3"_s.arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);

    if (GIT_TAG == version)
        return version;

    return version + '-'_L1 + VERSION_CHANNEL;
}();

const QString HELP_URL = u"@Launcher_HELP_URL@"_s;
const QString BUG_TRACKER_URL = u"@Launcher_BUG_TRACKER_URL@"_s;
const QString TRANSLATIONS_URL = u"@Launcher_TRANSLATIONS_URL@"_s;
const QString DISCORD_URL = u"@Launcher_DISCORD_URL@"_s;
const QString MATRIX_URL = u"@Launcher_MATRIX_URL@"_s;
const QString SUBREDDIT_URL = u"@Launcher_SUBREDDIT_URL@"_s;
const QString SOURCE_CODE_URL = u"@Launcher_SOURCE_CODE_URL@"_s;

const QString BUILD_DATE = u"@Launcher_BUILD_DATE@"_s;
const QString BUILD_PLATFORM = u"@Launcher_BUILD_PLATFORM@"_s;
const QString COMPILER_NAME = u"@CMAKE_CXX_COMPILER_ID@"_s;
const QString COMPILER_VERSION = u"@CMAKE_CXX_COMPILER_ID@"_s;
const QString COMPILER_TARGET_SYSTEM = u"@CMAKE_SYSTEM_NAME@"_s;
const QString COMPILER_TARGET_SYSTEM_VERSION = u"@CMAKE_SYSTEM_VERSION@"_s;
const QString COMPILER_TARGET_SYSTEM_PROCESSOR = u"@CMAKE_SYSTEM_PROCESSOR@"_s;
}  // namespace BuildConfig
