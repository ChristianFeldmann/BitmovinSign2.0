#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    color = BitmovinBlue;
}

AnimationConstantColor::AnimationConstantColor(QColor &color)
{
    this->color = color;
}

void AnimationConstantColor::renderFrame(Frame &frame)
{
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        frame.ledData[i] = this->color;
    }
}
