#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    color = LedColor(30, 171, 226);
}

AnimationConstantColor::AnimationConstantColor(LedColor &color)
{
    this->color = color;
}

void AnimationConstantColor::render_frame(Frame &frame)
{
    for (int i = 0; i < TOTAL_LEDS; i++)
    {
        frame.ledData[i] = this->color;
    }
}
