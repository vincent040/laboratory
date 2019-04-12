TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    __date.cpp \
    __time.cpp

HEADERS += \
    __date.h \
    __time.h

