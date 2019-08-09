#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>

class Frame
{
public:
    Frame(/* args */) {};
    ~Frame() {};

    void convertImageToByteArray() {};

private:
    QImage image;
    char led[1000];
};

