#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T00:44:40
#
#-------------------------------------------------

QT       += core gui
QT	 += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = udpSrv
TEMPLATE = app


SOURCES += main.cpp\
        udpsrv.cpp

HEADERS  += udpsrv.h

FORMS    += udpsrv.ui
