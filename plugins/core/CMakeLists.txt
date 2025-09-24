project(core)

qt_standard_project_setup()

qt_add_library(${PROJECT_NAME} STATIC
	include/core/bootstrap.h

	src/bootstrap.cpp
	src/CorePlugin.cpp
	src/CorePlugin.h
	src/ui/AboutDialog.h
	src/ui/AboutDialog.cpp
	src/ui/AboutDialog.ui
	src/ui/MainWindow.h
	src/ui/MainWindow.cpp
	src/ui/MainWindow.ui
)


target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Widgets common)

target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} PRIVATE include/core)

target_compile_definitions(${PROJECT_NAME} PRIVATE QT_STATICPLUGIN)
