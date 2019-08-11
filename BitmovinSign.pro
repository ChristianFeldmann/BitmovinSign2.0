QT += widgets

TARGET = bin/BitmovinSign
TEMPLATE = app
CONFIG += c++11


HEADERS += lib/ws2811/pwm.h
HEADERS += lib/ws2811/rpihw.h
HEADERS += lib/ws2811/mailbox.h
HEADERS += lib/ws2811/clk.h
HEADERS += lib/ws2811/gpio.h
HEADERS += lib/ws2811/dma.h
HEADERS += lib/ws2811/pcm.h
HEADERS += src/Output.h
HEADERS += src/DebuggerWidget.h
HEADERS += src/definitions.h
HEADERS += src/Frame.h
HEADERS += src/Player.h
HEADERS += src/AnimationInterface.h
HEADERS += src/AnimationHandler.h
HEADERS += src/animations/AnimationHighlightRotation.h
HEADERS += src/animations/AnimationRunningDot.h
HEADERS += src/animations/AnimationConstantColor.h

SOURCES += src/bitmovinSign.cpp
SOURCES += src/Output.cpp
SOURCES += lib/ws2811/pwm.c
SOURCES += lib/ws2811/ws2811.c
SOURCES += lib/ws2811/rpihw.c
SOURCES += lib/ws2811/mailbox.c
SOURCES += lib/ws2811/dma.c
SOURCES += lib/ws2811/pcm.c
SOURCES += src/DebuggerWidget.cpp
SOURCES += src/Player.cpp
SOURCES += src/AnimationHandler.cpp
SOURCES += src/animations/AnimationHighlightRotation.cpp
SOURCES += src/animations/AnimationRunningDot.cpp
SOURCES += src/animations/AnimationConstantColor.cpp

macx {

HEADERS -= lib/ws2811/pwm.h
HEADERS -= lib/ws2811/rpihw.h
HEADERS -= lib/ws2811/mailbox.h
HEADERS -= lib/ws2811/clk.h
HEADERS -= lib/ws2811/gpio.h
HEADERS -= lib/ws2811/dma.h
HEADERS -= lib/ws2811/pcm.h

SOURCES -= lib/ws2811/pwm.c
SOURCES -= lib/ws2811/ws2811.c
SOURCES -= lib/ws2811/rpihw.c
SOURCES -= lib/ws2811/mailbox.c
SOURCES -= lib/ws2811/dma.c
SOURCES -= lib/ws2811/pcm.c
}

win32 {

HEADERS -= lib/ws2811/pwm.h
HEADERS -= lib/ws2811/rpihw.h
HEADERS -= lib/ws2811/mailbox.h
HEADERS -= lib/ws2811/clk.h
HEADERS -= lib/ws2811/gpio.h
HEADERS -= lib/ws2811/dma.h
HEADERS -= lib/ws2811/pcm.h

SOURCES -= lib/ws2811/pwm.c
SOURCES -= lib/ws2811/ws2811.c
SOURCES -= lib/ws2811/rpihw.c
SOURCES -= lib/ws2811/mailbox.c
SOURCES -= lib/ws2811/dma.c
SOURCES -= lib/ws2811/pcm.c
}
