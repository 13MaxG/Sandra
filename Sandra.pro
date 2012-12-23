TEMPLATE = app
CONFIG += console
CONFIG -= qt

HEADERS += \
    system.h \
    key.h \
    argument.h \
    video.h \
    video.h \
    command.h \
    lissajous.h \
    convert.h \
    mandelbrot.h \
    image.h \
    operator.h \
    operatoritem.h

SOURCES += main.cpp \
    system.cpp \
    key.cpp \
    argument.cpp \
    video.cpp \
    command.cpp \
    lissajous.cpp \
    mandelbrot.cpp \
    image.cpp \
    operator.cpp \
    operatoritem.cpp

CONFIG += link_pkgconfig
PKGCONFIG += opencv


