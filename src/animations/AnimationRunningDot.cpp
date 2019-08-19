#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot()
{
    this->animationParameters.push_back(AnimationParameter("color", &this->color));
}

void AnimationRunningDot::reset()
{
    this->counter = 0;
}

bool AnimationRunningDot::renderFrame()
{
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        this->frame.data[i] = (i == this->counter) ? this->color : Qt::transparent;
    }

    this->counter++;
    if (this->counter > NR_LED_TOTAL)
    {
        this->counter = 0;
    }

    return this->counter == 0;
}
