#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T02:13:19
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcpSrv
TEMPLATE = app


SOURCES += main.cpp\
        tcpsrv.cpp \
    clientsock.cpp \
    server.cpp

HEADERS  += tcpsrv.h \
    clientsock.h \
    server.h

FORMS    += tcpsrv.ui
