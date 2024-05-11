QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArcherTower.cpp \
    Arrow.cpp \
    Bullet.cpp \
    Canon.cpp \
    CitizenWorker.cpp \
    ClanCastle.cpp \
    Defence.cpp \
    Enemy.cpp \
    Fence.cpp \
    Game.cpp \
    GameObject.cpp \
    Player.cpp \
    Potion.cpp \
    PowerUp.cpp \
    WizardTower.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ArcherTower.h \
    Arrow.h \
    Bullet.h \
    Canon.h \
    CitizenWorker.h \
    ClanCastle.h \
    Defence.h \
    Enemy.h \
    Fence.h \
    Game.h \
    GameObject.h \
    Player.h \
    Potion.h \
    PowerUp.h \
    WizardTower.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Files.qrc \
    sounds.qrc
