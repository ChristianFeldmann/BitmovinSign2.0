#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>

struct Led
{
    /* data */
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};


class Frame
{
public:
    Frame(/* args */) {};
    ~Frame() {};
    std::vector<Led> led;

    void convertImageToByteArray() {};

private:
    QImage image;
};