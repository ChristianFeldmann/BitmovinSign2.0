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
HEADERS += output/mailbox.h
HEADERS += output/clk.h
HEADERS += output/gpio.h
HEADERS += output/dma.h
HEADERS += output/pcm.h
HEADERS += helpers/debugger_widget.h
HEADERS += helpers/player.h

SOURCES += bitmovinSign.cpp
SOURCES += output/output.cpp
SOURCES += output/pwm.c
SOURCES += output/ws2811.c
SOURCES += output/rpihw.c
SOURCES += output/mailbox.c
SOURCES += output/dma.c
SOURCES += output/pcm.c
SOURCES += helpers/debugger_widget.cpp
SOURCES += helpers/player.cpp

