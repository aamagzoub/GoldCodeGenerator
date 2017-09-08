#-------------------------------------------------
#
# Project created by QtCreator 2017-08-31T16:04:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoldCodeGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mseqgena.cpp \
    mseqgenb.cpp

HEADERS  += mainwindow.h \
    mseqgena.h \
    mseqgenb.h

FORMS    += mainwindow.ui

win32:RC_ICONS += gold_code.ico

