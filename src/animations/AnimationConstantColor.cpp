#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    color = BITMOVIN_BLUE;
}

AnimationConstantColor::AnimationConstantColor(QColor &color)
{
    this->color = color;
}

bool AnimationConstantColor::renderFrame(Frame &frame)
{
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        frame[i] = this->color;
    }

    return true;
}
