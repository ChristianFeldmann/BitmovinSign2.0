#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor(AnimationTreeBase *parentStack) : 
    AnimationBase(parentStack)
{
    this->addParameter("color", &this->color);
}

bool AnimationConstantColor::renderAnimation(Frame &frame, QImage &image)
{
    Q_UNUSED(image);

    std::fill(frame.data.begin(), frame.data.end(), this->color);
    return true;
}
