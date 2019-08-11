#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>
#include <QColor>

#include "definitions.h"

struct Frame
{
    Frame(/* args */) {ledData = std::vector<QColor>(NR_LED_TOTAL);};
    ~Frame() {};

    QImage image;
    std::vector<QColor> ledData;
};