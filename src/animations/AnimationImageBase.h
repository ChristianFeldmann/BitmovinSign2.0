#pragma once

#include <AnimationInterface.h>
#include <Constants.h>
#include <QImage>

const unsigned imageWidth = 120;
const unsigned imageHeight = 120;
const QSize imageSize = QSize(imageWidth, imageHeight);

class AnimationImageBase: public AnimationInterface
{
public:
    AnimationImageBase();
    
    // The AnimationImageBase allows to render 2-dimensional images. These are then mapped
    // to the LED values in 'frame'. The implementation of this function is in this file.
    bool renderFrame(Frame &frame) override final;

    const QImage &getImage() { return this->image; }

protected:

    QImage image;

    // Overload this function in your inherited animation to render to the 2D image 'image'.
    // Return true if the animation ended.
    virtual bool renderImage() = 0;

private:

    std::vector<QPoint> ledsCoord;

    void calculateLedsCoord();

    void draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor);
    void draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots);
};
