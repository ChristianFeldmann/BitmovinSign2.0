#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    color = QColor(30, 171, 226);
}

AnimationRunningDot::AnimationRunningDot(QColor &color)
{
    this->color = color;
}

void AnimationRunningDot::renderFrame(Frame &frame)
{
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        if (this->counter == i)
        {
            frame.ledData[i] = this->color;
        }
        else
        {
            frame.ledData[i] = Qt::black;
        }
    }

    this->counter++;
    if (this->counter > 489)
    {
        this->counter = 0;
    }
}