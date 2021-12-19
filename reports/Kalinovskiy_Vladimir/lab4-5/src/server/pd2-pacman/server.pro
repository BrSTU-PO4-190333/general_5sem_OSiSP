QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app
TARGET = server

MOC_DIR     += generated/mocs
UI_DIR      += generated/uis
RCC_DIR     += generated/rccs
OBJECTS_DIR += generated/objs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    serverstuff.cpp

HEADERS += \
    mainwindow.h \
    serverstuff.h

FORMS += \
    mainwindow.ui
DISTFILES += \
    server.json

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
