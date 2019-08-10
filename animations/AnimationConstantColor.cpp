#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    color = Led(30, 171, 226);
}

AnimationConstantColor::AnimationConstantColor(Led &color)
{
    this->color = color;
}

void AnimationConstantColor::render_frame(Frame &frame)
{
    for (int i = 0; i < TOTAL_LEDS; i++)
    {
        frame.led[i] = this->color;
    }
}
