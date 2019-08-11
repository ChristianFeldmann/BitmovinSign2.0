#pragma once

#include <Frame.h>

class AnimationInterface
{
public:
    virtual void renderFrame(Frame &f) = 0;

    virtual ~AnimationInterface() = default;
};
