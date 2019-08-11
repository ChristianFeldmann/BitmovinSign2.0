#pragma once

#include <Constants.h>

class AnimationInterface
{
public:
    virtual ~AnimationInterface() = default;

    virtual bool renderFrame(Frame &f) = 0;
};
