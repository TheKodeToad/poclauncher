cmake_minimum_required(VERSION 3.22)

project(launcher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(cmark REQUIRED)

include(Variables)

qt_standard_project_setup()
qt_add_executable(${PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets common core)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

add_subdirectory(common)
add_subdirectory(plugins)
