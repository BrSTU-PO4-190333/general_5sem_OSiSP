cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/lib/qt5/bin")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(lab1 main.cpp tetrixboard.cpp tetrixboard.h tetrixpiece.cpp tetrixpiece.h tetrixwindow.cpp tetrixwindow.h)
target_link_libraries(lab1
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

