QT += widgets

TARGET = BitmovinSign
TEMPLATE = app
CONFIG += c++11

HEADERS += animations/animationInterface.h
HEADERS += effects/effectInterface.h
HEADERS += helpers/frame.h
HEADERS += helpers/output.h
HEADERS += helpers/debugger_widget.h

SOURCES += bitmovinSign.cpp
SOURCES += helpers/debugger_widget.cpp

