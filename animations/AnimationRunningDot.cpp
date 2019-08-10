#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    color = LedColor(30, 171, 226);
}

AnimationRunningDot::AnimationRunningDot(LedColor &color)
{
    this->color = color;
}

void AnimationRunningDot::render_frame(Frame &frame)
{
    for (int i = 0; i < TOTAL_LEDS; i++)
    {
        if (this->counter == i)
        {
            frame.ledData[i] = this->color;
        }
        else
        {
            frame.ledData[i] = LedColor::black;
        }
    }

    this->counter++;
    if (this->counter > 489)
    {
        this->counter = 0;
    }
}