#pragma once

#include "../helpers/frame.h"

class animationInterface
{
public:
    virtual void render_frame(Frame &f) = 0;
};
