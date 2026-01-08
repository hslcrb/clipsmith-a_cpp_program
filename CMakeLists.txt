cmake_minimum_required(VERSION 3.16)

project(Clipsmith VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt6를 먼저 시도하고, 없으면 Qt5를 찾습니다.
find_package(Qt6 COMPONENTS Core Gui Widgets Sql QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql)
    set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql)
    message(STATUS "Qt6 not found, using Qt5")
else()
    set(QT_LIBRARIES Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql)
    message(STATUS "Using Qt6")
endif()

add_executable(Clipsmith
    src/main.cpp
    src/core/ClipboardMonitor.cpp
    src/core/DatabaseManager.cpp
    src/gui/MainWindow.cpp
    src/plugins/TextProcessor.cpp
    resources/resources.qrc
)

target_link_libraries(Clipsmith PRIVATE ${QT_LIBRARIES})

install(TARGETS Clipsmith
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)

# --- CPack Packaging Configuration ---
set(CPACK_PACKAGE_NAME "Clipsmith")
set(CPACK_PACKAGE_VENDOR "Rhee Creative")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Premium Smart Clipboard Manager for professionals")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

# Windows Packager (.exe via NSIS)
if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_MODIFY_PATH ON)
endif()

# macOS Packager (.dmg)
if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
endif()

# Linux Packager (.deb, .tar.gz)
if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB;TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rheehose (Rhee Creative) & Gemini 3 Flash")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base-dev, libqt6sql6-sqlite")
endif()

include(CPack)
