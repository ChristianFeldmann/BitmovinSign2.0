#include "AnimationRunningDot.h"

AnimationRunningDot::AnimationRunningDot(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("color", &this->color);
}

void AnimationRunningDot::reset()
{
    this->counter = 0;
}

void AnimationRunningDot::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        frame.data[i] = (i == this->counter) ? this->color : Qt::transparent;
    }

    this->counter++;
    if (this->counter > NR_LED_TOTAL)
    {
        this->counter = 0;
    }
}

AnimationState AnimationRunningDot::getState()
{
    if (this->counter == 0)
        return AnimationState::SwitchNow;
    return AnimationState::Running;
}
