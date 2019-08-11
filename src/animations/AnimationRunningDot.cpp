#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    color = QColor(30, 171, 226);
    color = Qt::red;
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
            frame.push_back(this->color);
        }
        else
        {
            frame.push_back(Qt::white);
        }
    }

    this->counter++;
    if (this->counter > 489)
    {
        this->counter = 0;
        return false;
    }

    return true;
}
