#pragma once

#include "AnimationInterface.h"

/* A stack of multiple animations. Rendering the stack will render all animations
 * in the order they were added.
 */
class AnimationStack : public AnimationInterface
{
public:
    AnimationStack() = default;
    ~AnimationStack() = default;

    virtual bool renderFrame(Frame &f);

    void addAnimation(std::shared_ptr<AnimationInterface> animation);

private:
    std::vector<std::shared_ptr<AnimationInterface>> animations;

    unsigned animationsFinished{ 0 };
};
