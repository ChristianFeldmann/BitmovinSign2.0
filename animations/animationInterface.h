#pragma once

#include "../helpers/frame.h"

class AnimationInterface
{
public:
    virtual void render_frame(Frame &f) = 0;
};
