#pragma once

#include "AnimationInterface.h"

#include <memory>

class AnimationHandler
{
public:
    AnimationHandler() = default;

    std::unique_ptr<AnimationInterface> getNextAnimation();
};
