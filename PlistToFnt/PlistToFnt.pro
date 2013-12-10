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
    libs/fnt/fntserializer.cpp \
    libs/qtplist/PListParser.cpp \
    libs/qtplist/PListSerializer.cpp \
    gsetting.cpp

HEADERS  += dialog.h \
    libs/fnt/fntserializer.h \
    libs/qtplist/PListParser.h \
    libs/qtplist/PListSerializer.h \
    gsetting.h

FORMS    += dialog.ui

OTHER_FILES += \
    README.txt

