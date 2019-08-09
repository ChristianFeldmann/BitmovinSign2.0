#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>

#define TOTAL_LEDS 489

struct Led
{
    /* data */
    char red;
    char green;
    char blue;
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