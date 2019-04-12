#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T20:40:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app


SOURCES += main.cpp\
        chatserver.cpp \
    chatclientsocket.cpp

HEADERS  += chatserver.h \
    chatclientsocket.h

FORMS    += chatserver.ui
