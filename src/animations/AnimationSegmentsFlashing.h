#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationSegmentsFlashing : public AnimationInterface
{
public:
    AnimationSegmentsFlashing();
    
    bool renderFrame() override;
    virtual QString getName() override { return "SegmentsFlashing"; };
    void reset() override;

private:
    QColor color{ BITMOVIN_BLUE };

    unsigned counter{ 0 };
    int timeOffsetBetweenSegments{ 0 };
    int timeToWaitFullColor{ 0 };
};

