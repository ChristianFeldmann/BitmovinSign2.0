QT += widgets

TARGET = BitmovinSign
TEMPLATE = app
CONFIG += c++11

HEADERS += animations/animationInterface.h
HEADERS += effects/effectInterface.h
HEADERS += helpers/frame.h
HEADERS += output/output.h
HEADERS += output/pwm.h
HEADERS += output/rpihw.h

SOURCES += bitmovinSign.cpp
SOURCES += output/output.cpp
SOURCES += output/pwm.c
SOURCES += output/ws2811.c
SOURCES += output/pwm.c
SOURCES += output/rpihw.c
