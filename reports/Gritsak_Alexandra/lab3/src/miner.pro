QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    endwindow.cpp \
    game.cpp \
    main.cpp \
    settingswindow.cpp \
    startwindow.cpp

HEADERS += \
    endwindow.h \
    game.h \
    settingswindow.h \
    startwindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-about-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release/ -labout
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-about-Desktop_Qt_6_1_3_MinGW_64_bit-Release/debug/ -labout

INCLUDEPATH += $$PWD/../../../build-about-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release
DEPENDPATH += $$PWD/../../../build-about-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-helper_class-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release/ -lhelper_class
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-helper_class-Desktop_Qt_6_1_3_MinGW_64_bit-Release/debug/ -lhelper_class

INCLUDEPATH += $$PWD/../../../build-helper_class-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release
DEPENDPATH += $$PWD/../../../build-helper_class-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-helper-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release/ -lHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-helper-Desktop_Qt_6_1_3_MinGW_64_bit-Release/debug/ -lHelper

INCLUDEPATH += $$PWD/../../../build-helper-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release
DEPENDPATH += $$PWD/../../../build-helper-Desktop_Qt_6_1_3_MinGW_64_bit-Release/release
