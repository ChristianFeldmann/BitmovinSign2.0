#pragma once

#include "AnimationInterface.h"

#include <memory>

class AnimationHandler
{
public:
    AnimationHandler() = default;

    void createNextAnimationStack(std::vector<std::unique_ptr<AnimationInterface>> &animationList, unsigned int animationIndex=0);
};
