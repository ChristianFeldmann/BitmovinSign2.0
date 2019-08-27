#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor(AnimationTreeBase *parentStack) : 
    AnimationBase(parentStack)
{
    this->animationParameters.push_back(std::make_shared<AnimationParameter>(this, "color", &this->color));
}

bool AnimationConstantColor::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);

    std::fill(frame.data.begin(), frame.data.end(), this->color);
    return true;
}
