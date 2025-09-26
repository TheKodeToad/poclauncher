project(NewsPlugin)

qt_standard_project_setup()

qt_add_plugin(
	${PROJECT_NAME} STATIC
	include/NewsPlugin/NewsPlugin.h

	src/NewsPlugin.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Widgets Core)

target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} PRIVATE include/NewsPlugin)

target_compile_definitions(${PROJECT_NAME} PRIVATE QT_STATICPLUGIN)
