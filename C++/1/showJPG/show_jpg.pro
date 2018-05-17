TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wrap.c \
    lcd.cpp \
    image.cpp

INCLUDEPATH += ./jpeg-9.0/include
LIBS        += -L./jpeg-9.0/lib -ljpeg

HEADERS += \
    wrap.h \
    lcd.h \
    image.h
