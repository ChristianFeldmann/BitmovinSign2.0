#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    color = QColor(30, 171, 226);
    color = Qt::red;
}

void AnimationRunningDot::reset()
{
    this->counter = 0;
}

AnimationRunningDot::AnimationRunningDot(QColor &color)
{
    this->color = color;
}

bool AnimationRunningDot::renderFrame(Frame &frame)
{
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        if (this->counter == i)
        {
            frame[i] = this->color;
        }
        else
        {
            frame[i] = Qt::black;
        }
    }

    this->counter++;
    if (this->counter > NR_LED_TOTAL)
    {
        this->counter = 0;
    }

    return this->counter == 0;
}
