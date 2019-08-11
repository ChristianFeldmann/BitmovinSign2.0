#pragma once

#include "../helpers/frame.h"

class AnimationInterface
{
public:
    virtual void renderFrame(Frame &f) = 0;
};
