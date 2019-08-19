#include "AnimationConstantColor.h"

AnimationConstantColor::AnimationConstantColor()
{
    this->animationParameters.push_back(AnimationParameter("color", &this->color));
}

bool AnimationConstantColor::renderFrame()
{
    std::fill(this->frame.data.begin(), this->frame.data.end(), this->color);
    return true;
}
