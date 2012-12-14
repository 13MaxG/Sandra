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
    convert.h

SOURCES += main.cpp \
    system.cpp \
    key.cpp \
    argument.cpp \
    video.cpp \
    command.cpp \
    lissajous.cpp

CONFIG += link_pkgconfig
PKGCONFIG += opencv


