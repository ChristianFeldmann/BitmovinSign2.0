#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>
#include <QColor>

#define TOTAL_LEDS 489

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
};

struct Frame
{
    Frame(/* args */) {ledData = std::vector<LedColor>(TOTAL_LEDS);};
    ~Frame() {};

    void convertImageToByteArray() {};

    QImage image;
    std::vector<LedColor> ledData;
};