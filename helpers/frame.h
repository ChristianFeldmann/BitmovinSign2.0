#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>
#include <QColor>

#include "definitions.h"

struct LedColor
{
    LedColor() {};
    LedColor(unsigned char red, unsigned char green, unsigned char blue) :
        red(red), green(green), blue(blue) {}
    QColor getQColor() { return QColor(red, green, blue); }

    /* data */
    unsigned char red {0};
    unsigned char green {0};
    unsigned char blue {0};

    static LedColor black;
    static LedColor white;
    static LedColor bitmovinBlue;
};

struct Frame
{
    Frame(/* args */) {ledData = std::vector<LedColor>(NR_LED_TOTAL);};
    ~Frame() {};

    void convertImageToByteArray() {};

    QImage image;
    std::vector<LedColor> ledData;
};