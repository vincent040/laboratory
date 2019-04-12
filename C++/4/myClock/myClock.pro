TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
SOURCES += myclock.cpp

LIBS += -lpthread

HEADERS += myclock.h

QMAKE_CFLAGS += "-std=c++11"
