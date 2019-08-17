#include "AnimationStack.h"

bool AnimationStack::renderFrame(Frame &f)
{
    for (auto animation : this->animations)
    {
        if (animation->renderFrame(f))
        {
            animationsFinished++;
        }
    }
    if (animationsFinished > 0 && animationsFinished == this->animations.size())
    {
        animationsFinished = 0;
        return true;
    }
    return false;
}

void AnimationStack::addAnimation(std::shared_ptr<AnimationInterface> animation)
{
    this->animations.push_back(animation);
}
