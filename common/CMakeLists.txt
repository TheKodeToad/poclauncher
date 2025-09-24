set(PARENT_PROJECT_NAME ${PROJECT_NAME})
set(PARENT_PROJECT_VERSION ${PROJECT_VERSION})
project(common)

configure_file(src/BuildConfig.in.cpp src/BuildConfig.cpp)

qt_add_library(${PROJECT_NAME}
	include/common/BuildConfig.h
	include/common/CustomMessageBox.h

	src/BuildConfig.cpp
	src/CustomMessageBox.cpp
	src/Markdown.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets cmark)

target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} PRIVATE include/common src)

# public in order for every plugin to have these definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC QT_NO_CAST_FROM_ASCII QT_NO_URL_CAST_FROM_STRING QT_NO_CAST_FROM_BYTEARRAY)
