cmake_minimum_required(VERSION 3.16)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

project(uu VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui Multimedia Network Concurrent Test REQUIRED)
qt_standard_project_setup(REQUIRES 6.5)

find_package(QWindowKit COMPONENTS Core Widgets Quick REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)
add_subdirectory(entities)
add_subdirectory(network)
add_subdirectory(service)
add_subdirectory(controller)
add_subdirectory(ui_base)
add_subdirectory(gui)
#add_subdirectory(test)

qt_add_executable(uu
    main.cc
)

target_link_libraries(uu PRIVATE Qt6::Gui Qt6::Quick Qt6::Network controller gui guiplugin engine network service QWindowKit::Quick)
