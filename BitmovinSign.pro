QT += widgets

TARGET = BitmovinSign
TEMPLATE = app
CONFIG += c++11

HEADERS += output/Output.h
HEADERS += output/pwm.h
HEADERS += output/rpihw.h
HEADERS += output/mailbox.h
HEADERS += output/clk.h
HEADERS += output/gpio.h
HEADERS += output/dma.h
HEADERS += output/pcm.h
HEADERS += helpers/DebuggerWidget.h
HEADERS += helpers/definitions.h
HEADERS += helpers/Frame.h
HEADERS += helpers/Player.h
HEADERS += animations/AnimationInterface.h
HEADERS += animations/AnimationHandler.h
HEADERS += animations/AnimationHighlightRotation.h
HEADERS += animations/AnimationRunningDot.h
HEADERS += animations/AnimationConstantColor.h

SOURCES += bitmovinSign.cpp
SOURCES += output/Output.cpp
SOURCES += output/pwm.c
SOURCES += output/ws2811.c
SOURCES += output/rpihw.c
SOURCES += output/mailbox.c
SOURCES += output/dma.c
SOURCES += output/pcm.c
SOURCES += helpers/DebuggerWidget.cpp
SOURCES += helpers/Frame.cpp
SOURCES += helpers/Player.cpp
SOURCES += animations/AnimationHandler.cpp
SOURCES += animations/AnimationHighlightRotation.cpp
SOURCES += animations/AnimationRunningDot.cpp
SOURCES += animations/AnimationConstantColor.cpp

macx {

HEADERS -= output/pwm.h
HEADERS -= output/rpihw.h
HEADERS -= output/mailbox.h
HEADERS -= output/clk.h
HEADERS -= output/gpio.h
HEADERS -= output/dma.h
HEADERS -= output/pcm.h

SOURCES -= output/pwm.c
SOURCES -= output/ws2811.c
SOURCES -= output/rpihw.c
SOURCES -= output/mailbox.c
SOURCES -= output/dma.c
SOURCES -= output/pcm.c
}

win32 {

HEADERS -= output/pwm.h
HEADERS -= output/rpihw.h
HEADERS -= output/mailbox.h
HEADERS -= output/clk.h
HEADERS -= output/gpio.h
HEADERS -= output/dma.h
HEADERS -= output/pcm.h

SOURCES -= output/pwm.c
SOURCES -= output/ws2811.c
SOURCES -= output/rpihw.c
SOURCES -= output/mailbox.c
SOURCES -= output/dma.c
SOURCES -= output/pcm.c
}
