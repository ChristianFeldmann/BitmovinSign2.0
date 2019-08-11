#pragma once

#include "../AnimationInterface.h"
#include "../frame.h"

class AnimationRunningDot: public AnimationInterface
{
public:
    AnimationRunningDot();
    AnimationRunningDot(QColor &color);
    void renderFrame(Frame &frame) override;

private:
    int counter {0};
    QColor color;
};

