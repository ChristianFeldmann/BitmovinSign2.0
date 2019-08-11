#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    color = LedColor(30, 171, 226);
}

AnimationRunningDot::AnimationRunningDot(LedColor &color)
{
    this->color = color;
}

void AnimationRunningDot::renderFrame(Frame &frame)
{
    for (int i = 0; i < NR_LED_TOTAL; i++)
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