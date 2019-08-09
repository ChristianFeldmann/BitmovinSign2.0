#pragma once

#include "animationInterface.h"
#include "../helpers/frame.h"

class animation1: public animationInterface
{
private:
    /* data */
    int counter {0};
public:
    void render_frame(Frame &frame) override;
};

