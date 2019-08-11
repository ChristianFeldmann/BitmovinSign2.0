#pragma once

#include "frame.h"

class AnimationInterface
{
public:
    virtual void renderFrame(Frame &f) = 0;
};
