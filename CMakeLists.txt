cmake_minimum_required(VERSION 3.5)

project(PhysFitPWD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)

set(PRJ_RESOURCES)
set(PRJ_DEFINES)
set(PRJ_SRCS)

file(GLOB_RECURSE PRJ_SRCS0 "src/*.h" "src/*.hpp" "src/*.cpp" "src/*.ui")
list(APPEND PRJ_SRCS ${PRJ_SRCS0})

add_executable(PhysFitPWD
    ${PROJECT_SOURCES}
    src/tests/testexesiseform.h src/tests/testexesiseform.cpp src/tests/testexesiseform.ui
    )

list(APPEND PRJ_RESOURCES
    "src/res.qrc"
    )

target_sources(${PROJECT_NAME} PRIVATE ${PRJ_SRCS} ${PRJ_UIS} ${PRJ_RESOURCES} ${QM_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(PhysFitPWD
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(PhysFitPWD PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)
include(GNUInstallDirs)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PhysFitPWD)
endif()


