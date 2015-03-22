#-------------------------------------------------
#
# Project created by QtCreator 2013-03-26T18:48:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefence
TEMPLATE = app


SOURCES += main.cpp\
    towers.cpp \
    field.cpp \
    creeps.cpp \
    mainmenu.cpp \
    widgetcontroller.cpp \
    optionmenu.cpp \
    choosemapmenu.cpp \
    gamewidget.cpp \
    faction.cpp \
    tower.cpp \
    creep.cpp \
    defaultunit.cpp \
    defaulttower.cpp

HEADERS  += \
    towers.h \
    field.h \
    creeps.h \
    mainmenu.h \
    widgetcontroller.h \
    optionmenu.h \
    choosemapmenu.h \
    gamewidget.h \
    faction.h \
    tower.h \
    creep.h \
    defaultunit.h \
    defaulttower.h

FORMS    += \
    mainmenu.ui \
    optionmenu.ui \
    choosemapmenu.ui \
    gamewidget.ui
