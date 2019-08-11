#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationRunningDot: public AnimationInterface
{
public:
    AnimationRunningDot();
    AnimationRunningDot(QColor &color);
    
    bool renderFrame(Frame &frame) override;

private:
    unsigned counter {0};
    QColor color;
};
