TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += opengl
QT += core gui opengl widgets

SOURCES += main.cpp \
    grid.cpp \
    creature.cpp \
    display.cpp \
    coords.cpp \
    predator.cpp \
    prey.cpp \
    random.cpp \
    bomber.cpp \
    draw.cpp \
    god.cpp

HEADERS += \
    grid.h \
    creature.h \
    display.h \
    gConst.h \
    coords.h \
    predator.h \
    prey.h \
    random.h \
    bomber.h \
    draw.h \
    god.h

