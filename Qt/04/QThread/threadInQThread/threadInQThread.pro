#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T15:21:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = threadInQThread
TEMPLATE = app


SOURCES += main.cpp\
        controller.cpp \
    worker.cpp

HEADERS  += controller.h \
    worker.h

FORMS    += controller.ui
