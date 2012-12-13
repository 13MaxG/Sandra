TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    system.cpp \
    key.cpp \
    argument.cpp \
    video.cpp

CONFIG += link_pkgconfig
PKGCONFIG += opencv

HEADERS += \
    system.h \
    key.h \
    argument.h \
    video.h
