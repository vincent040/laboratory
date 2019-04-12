#-------------------------------------------------
#
# Project created by QtCreator 2016-05-22T20:29:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShowTime
TEMPLATE = app


SOURCES += main.cpp\
        showtime.cpp \
    mythread.cpp

HEADERS  += showtime.h \
    mythread.h

FORMS    += showtime.ui
