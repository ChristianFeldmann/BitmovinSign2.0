#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    color = Led(30, 171, 226);
}

AnimationRunningDot::AnimationRunningDot(Led &color)
{
    this->color = color;
}

void AnimationRunningDot::render_frame(Frame &frame)
{
    for (int i = 0; i < TOTAL_LEDS; i++)
    {
        if (this->counter == i)
        {
            frame.led[i] = this->color;
        }
        else
        {
            frame.led[i] = Led();
        }
    }

    this->counter++;
    if (this->counter > 489)
    {
        this->counter = 0;
    }
}