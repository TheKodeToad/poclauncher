cmake_minimum_required(VERSION 3.22)

project(Launcher)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(GetGitRevisionDescription)

set(Launcher_NAME "POCLauncher")
set(Launcher_BINARY_NAME "poclauncher")
set(Launcher_DISPLAY_NAME "POC Launcher" CACHE STRING "The friendly display name of the launcher")
set(Launcher_APP_ID "org.poclauncher.POCLauncher")
set(Launcher_COPYRIGHT "© 2025 TheKodeToad\\n© 2022-2025 Prism Launcher Contributors\\n© 2021-2022 PolyMC Contributors\\n© 2012-2021 MultiMC Contributors")
set(Launcher_Domain "poclauncher.org" CACHE STRING "The domain of the launcher")

set(Launcher_HELP_URL "https://prismlauncher.org/wiki/help-pages/%1" CACHE STRING "URL for launcher help action (%1 replaced with page name)")
set(Launcher_BUG_TRACKER_URL "https://github.com/TheKodeToad/poclauncher/issues" CACHE STRING "URL for the bug tracker")
set(Launcher_MATRIX_URL "https://prismlauncher.org/matrix" CACHE STRING "Matrix URL")
set(Launcher_DISCORD_URL "https://prismlauncher.org/discord" CACHE STRING "Discord URL")
set(Launcher_SUBREDDIT_URL "https://prismlauncher.org/reddit" CACHE STRING "Subreddit URL")
set(Launcher_SOURCE_CODE_URL "https://github.com/TheKodeToad/poclauncher" CACHE STRING "Subreddit URL")
set(Launcher_VERSION_MAJOR 1)
set(Launcher_VERSION_MINOR 0)
set(Launcher_VERSION_PATCH 0)

string(TIMESTAMP TODAY "%Y-%m-%d")
set(Launcher_BUILD_DATE ${TODAY})
set(Launcher_BUILD_PLATFORM "Unknown" CACHE STRING "A short string - shown in the about dialog - identifying the platform that this build was built for")

git_get_exact_tag(Launcher_GIT_TAG)
get_git_head_revision(Launcher_GIT_REFSPEC Launcher_GIT_COMMIT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -fsanitize=address,leak)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(cmark REQUIRED)

add_subdirectory(Core)
add_subdirectory(NewsPlugin)

qt_standard_project_setup()
qt_add_executable(${Launcher_BINARY_NAME} main.cpp)

target_link_libraries(${Launcher_BINARY_NAME} PRIVATE Qt6::Widgets Core)

set_target_properties(${Launcher_BINARY_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
