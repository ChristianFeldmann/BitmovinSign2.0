QT += gui

TARGET = BitmovinSign
TEMPLATE = app
CONFIG += c++11

HEADERS += animations/animationInterface.h
HEADERS += effects/effectInterface.h
HEADERS += helpter/signDrawer.h
HEADERS += helpter/signOutput.h

SOURCES += bitmovinSign.cpp

