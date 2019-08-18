#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    color = BITMOVIN_BLUE;
}

AnimationConstantColor::AnimationConstantColor(QColor &color)
{
    this->color = color;
}

bool AnimationConstantColor::renderFrame()
{
    std::fill(this->frame.data.begin(), this->frame.data.end(), this->color);
    return true;
}
