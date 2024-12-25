QT       += core gui
QT += core gui multimedia
QT += core gui network
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameSettingsWindow.cpp \
    InputManager.cpp \
    block.cpp \
    board.cpp \
    endlessmodewindow.cpp \
    game.cpp \
    gameendwindow.cpp \
    gamemodeWindow.cpp \
    levelgame.cpp \
    levelselectwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GameSettingsWindow.h \
    block.h \
    board.h \
    endlessmodewindow.h \
    game.h \
    gameendwindow.h \
    gamemodeWindow.h \
    inputmanager.h \
    levelgame.h \
    levelselectwindow.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
