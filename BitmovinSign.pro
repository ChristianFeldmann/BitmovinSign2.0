QT += xml

TARGET = bin/BitmovinSign
TEMPLATE = app
CONFIG += c++14
CONFIG += console
CONFIG -= flat

INCLUDEPATH += lib
INCLUDEPATH += src

# The output library
HEADERS += $$files(lib/*.h, true)
SOURCES += $$files(lib/*.c, true)

HEADERS += $$files(src/animation/*.h, true)
SOURCES += $$files(src/animation/*.cpp, true)
HEADERS += $$files(src/common/*.h, true)
SOURCES += $$files(src/common/*.cpp, true)

SOURCES += "src/Main.cpp"

macx {
    HEADERS -= $$files(lib/ws2811/*.h, true)
    SOURCES -= $$files(lib/ws2811/*.c, true)
    INCLUDEPATH -= lib
    CONFIG += editor
}

win32 {
    HEADERS -= $$files(lib/ws2811/*.h, true)
    SOURCES -= $$files(lib/ws2811/*.c, true)
    INCLUDEPATH -= lib
    CONFIG += editor
}
