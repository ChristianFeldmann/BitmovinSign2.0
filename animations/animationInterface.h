#pragma once

#include "../helpers/frame.h"

class animationInterface
{
public:
    animationInterface();
    ~animationInterface();

    virtual void render_frame(Frame &f) = 0;
};
