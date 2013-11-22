#-------------------------------------------------
#
# Project created by QtCreator 2013-11-21T20:20:13
#
#-------------------------------------------------

QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlistToFnt
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    libs/qtplist/PListParser.cpp \
    libs/qtplist/PListSerializer.cpp \
    libs/fnt/fntserializer.cpp

HEADERS  += dialog.h \
    libs/qtplist/PListParser.h \
    libs/qtplist/PListSerializer.h \
    libs/fnt/fntserializer.h

FORMS    += dialog.ui

