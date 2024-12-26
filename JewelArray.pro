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
    audiomanager.cpp \
    block.cpp \
    board.cpp \
    endlessmodewindow.cpp \
    game.cpp \
    gameendwindow.cpp \
    gamemodeWindow.cpp \
    historywindow.cpp \
    levelgame.cpp \
    levelselectwindow.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GameSettingsWindow.h \
    audiomanager.h \
    block.h \
    board.h \
    database.h \
    endlessmodewindow.h \
    game.h \
    gameendwindow.h \
    gamemodeWindow.h \
    historywindow.h \
    inputmanager.h \
    levelgame.h \
    levelselectwindow.h \
    logindialog.h \
    mainwindow.h \
    ui_mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    music.qrc \
    pic.qrc \
    pic.qrc

SUBDIRS += \
    Renderer.pro

DISTFILES += \
    000调用方法教程.txt \
    1.jpg \
    JewelArray.pro.user \
    LevelBackground.png \
    PopupBackground.png \
    README.md \
    Renderer.pro.user \
    Renderer.pro.user.1adb204 \
    Renderer.pro_BACKUP_152.user \
    Renderer.pro_BASE_152.user \
    Renderer.pro_LOCAL_152.user \
    Renderer.pro_REMOTE_152.user \
    Settings.png \
    add.png \
    alarm.png \
    button.png \
    change.png \
    default.png \
    fail.png \
    gem0.png \
    gem1.png \
    gem2.png \
    gem3.png \
    gems.png \
    succeed.png
