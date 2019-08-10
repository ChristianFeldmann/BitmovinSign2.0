#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationRunningDot: public AnimationInterface
{
public:
    AnimationRunningDot();
    AnimationRunningDot(LedColor &color);
    void render_frame(Frame &frame) override;

private:
    int counter {0};
    LedColor color;
};

