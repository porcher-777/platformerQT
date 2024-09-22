QT       += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Door.cpp \
    Enemy.cpp \
    Menu.cpp \
    MyScene.cpp \
    MyView.cpp \
    Player.cpp \
    Playerdialog.cpp \
    Soul.cpp \
    Stopwatch.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Door.h \
    Enemy.h \
    MainWindow.h \
    Menu.h \
    MyScene.h \
    MyView.h \
    Player.h \
    Playerdialog.h \
    Soul.h \
    Stopwatch.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
