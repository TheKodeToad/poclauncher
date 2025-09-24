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

using namespace Qt::Literals;

namespace BuildConfig {
static QString versionChannel() {
    static const QString PREFIX = u"refs/heads/"_s;

    if (GIT_REFSPEC.startsWith(PREFIX))
        return GIT_REFSPEC.mid(PREFIX.length());
    else if (!GIT_COMMIT.isEmpty())
        return GIT_COMMIT.mid(0, 8);
    else
        return GIT_REFSPEC;
}
static QString versionString()
{
    QString version = u"%1.%2.%3"_s.arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);

    if (GIT_TAG == version)
        return version;

    return version + '-'_L1 + VERSION_CHANNEL;
}


const QString LAUNCHER_NAME = u"@launcher_NAME@"_s;
const QString LAUNCHER_DISPLAYNAME = u"@launcher_DISPLAY_NAME@"_s;
const QString LAUNCHER_APP_BINARY_NAME = u"@PARENT_PROJECT_NAME@"_s;
const QString LAUNCHER_COPYRIGHT = u"@launcher_COPYRIGHT@"_s;

const QString GIT_COMMIT = u"@launcher_GIT_COMMIT@"_s;
const QString GIT_TAG = u"@launcher_GIT_TAG@"_s;
const QString GIT_REFSPEC = u"@launcher_GIT_REFSPEC@"_s;

// clang-format off
const int VERSION_MAJOR = @launcher_VERSION_MAJOR@;
const int VERSION_MINOR = @launcher_VERSION_MINOR@;
const int VERSION_PATCH = @launcher_VERSION_PATCH@;
// clang-format on
const QString VERSION_CHANNEL = versionChannel();
const QString VERSION_STRING = versionString();

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
}  // namespace BuildConfig
