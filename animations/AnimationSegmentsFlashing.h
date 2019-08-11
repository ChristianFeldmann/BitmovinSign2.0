#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationSegmentsFlashing : public AnimationInterface
{
public:
    AnimationSegmentsFlashing();
    AnimationSegmentsFlashing(LedColor &color, unsigned int timeOffsetBetweenSegments=20, unsigned int timeToWaitFullColor = 0);
    
    void renderFrame(Frame &frame) override;

private:
    LedColor color;

    unsigned int counter{ 0 };
    unsigned int timeOffsetBetweenSegments{ 0 };
    unsigned int timeToWaitFullColor{ 0 };
};

