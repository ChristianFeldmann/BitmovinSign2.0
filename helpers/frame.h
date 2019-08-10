#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>

#define TOTAL_LEDS 489

struct Led
{
    Led() {};
    Led(unsigned char red, unsigned char green, unsigned char blue) :
        red(red), green(green), blue(blue) {}

    /* data */
    unsigned char red {0};
    unsigned char green {0};
    unsigned char blue {0};
};


class Frame
{
public:
    Frame(/* args */) {led = std::vector<Led>(TOTAL_LEDS);};
    ~Frame() {};
    std::vector<Led> led;

    void convertImageToByteArray() {};

private:
    QImage image;
};