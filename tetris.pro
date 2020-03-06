#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T17:30:59
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = tetris
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    tetris.cpp \
    glass.cpp \
    figure.cpp \
    nextfigure.cpp

HEADERS  += tetris.h \
    glass.h \
    figure.h \
    nextfigure.h

FORMS    += tetris.ui

RESOURCES += \
    images.qrc

RC_FILE = tetris.rc
