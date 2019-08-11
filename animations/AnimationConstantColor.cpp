#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    color = LedColor::bitmovinBlue;
}

AnimationConstantColor::AnimationConstantColor(LedColor &color)
{
    this->color = color;
}

void AnimationConstantColor::renderFrame(Frame &frame)
{
    for (unsigned int i = 0; i < NR_LED_TOTAL; i++)
    {
        frame.ledData[i] = this->color;
    }
}
