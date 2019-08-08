QT += widgets

TARGET = BitmovinSign
TEMPLATE = app
CONFIG += c++11

HEADERS += animations/animationInterface.h
HEADERS += effects/effectInterface.h
HEADERS += helpers/signDrawer.h
HEADERS += helpers/signOutput.h

SOURCES += bitmovinSign.cpp

