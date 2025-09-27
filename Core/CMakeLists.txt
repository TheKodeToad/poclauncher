set(PARENT_PROJECT_NAME ${PROJECT_NAME})
set(PARENT_PROJECT_VERSION ${PROJECT_VERSION})
project(Core)

configure_file(src/BuildConfig.in.cpp src/BuildConfig.cpp)

qt_standard_project_setup()
qt_add_library(${PROJECT_NAME} STATIC
	include/Core/BuildConfig.h
	include/Core/PluginLoader.h
	include/Core/util/Markdown.h
	include/Core/util/MessageBox.h

	res/docs/docs.qrc
	res/icons/icons.qrc
	res/icons/multimc/multimc.qrc

	src/Application.cpp
	src/BuildConfig.cpp
	src/main.cpp
	src/PluginLoader.cpp
	src/StaticPluginImports.cpp
	src/ui/AboutDialog.h
	src/ui/AboutDialog.cpp
	src/ui/AboutDialog.ui
	src/ui/MainWindow.h
	src/ui/MainWindow.cpp
	src/ui/MainWindow.ui
	src/util/DesktopServices.cpp
	src/util/Markdown.cpp
	src/util/MessageBox.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets cmark NewsPlugin)

target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} PRIVATE include/Core src)

# public in order for every plugin to have these definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC QT_NO_CAST_FROM_ASCII QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_FROM_BYTEARRAY)

