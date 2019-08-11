QT += widgets

TARGET = bin/BitmovinSign
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/lib
INCLUDEPATH += $$PWD/src

HEADERS += $$files(lib/*.h, true)
HEADERS += $$files(src/*.h, true)

SOURCES += $$files(lib/*.c, true)
SOURCES += $$files(lib/*.cpp, true)
SOURCES += $$files(src/*.c, true)
SOURCES += $$files(src/*.cpp, true)

macx {
HEADERS -= $$files(lib/ws2811/*.h, true)
SOURCES -= $$files(lib/ws2811/*.c, true)
}

win32 {
HEADERS -= $$files(lib/ws2811/*.h, true)
SOURCES -= $$files(lib/ws2811/*.c, true)
}
