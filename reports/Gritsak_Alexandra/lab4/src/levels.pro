QT += core gui
QT += widgets

TARGET = Levels
TEMPLATE = lib
DEFINES += LEVELS_LIBRARY

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS=

SOURCES += \
    levels.cpp

HEADERS += \
    levels.h \
    levels_global.h

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
