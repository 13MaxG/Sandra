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
    operatoritem.h \
    buddhabrot.h \
    random.h \
    spiral.h \
    attractor.h \
    attractor_connections.h \
    ikeda.h \
    polynomial.h

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
    operatoritem.cpp \
    buddhabrot.cpp \
    random.cpp \
    spiral.cpp \
    attractor.cpp \
    attractor_connections.cpp \
    ikeda.cpp \
    polynomial.cpp

CONFIG += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /usr/include
LIBS += -L"/usr/include/boost" -lboost_system -lboost_filesystem
