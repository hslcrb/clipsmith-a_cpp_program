cmake_minimum_required(VERSION 3.16)

project(Clipsmith VERSION 0.1.0 LANGUAGES CXX)

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
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
