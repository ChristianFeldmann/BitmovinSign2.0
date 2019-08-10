#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationRunningDot: public AnimationInterface
{
public:
    AnimationRunningDot();
    AnimationRunningDot(Led &color);
    void render_frame(Frame &frame) override;

private:
    int counter {0};
    Led color;
};

