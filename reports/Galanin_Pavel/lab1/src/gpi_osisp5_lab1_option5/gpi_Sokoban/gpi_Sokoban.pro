QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gpi_gamewindow.cpp \
    gpi_gamewindow__gpi_drawAxes.cpp \
    gpi_gamewindow__gpi_drawTextures.cpp \
    gpi_gamewindow__gpi_generateLevel1.cpp \
    gpi_gamewindow__gpi_goBottom.cpp \
    gpi_gamewindow__gpi_goLeft.cpp \
    gpi_gamewindow__gpi_goRight.cpp \
    gpi_gamewindow__gpi_goTop.cpp \
    gpi_gamewindow__gpi_sayWon.cpp \
    main.cpp \
    gpi_mainwindow.cpp

HEADERS += \
    gpi_gamewindow.hpp \
    gpi_mainwindow.hpp

FORMS += \
    gpi_gamewindow.ui \
    gpi_mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gpi_gamewindow.qrc
