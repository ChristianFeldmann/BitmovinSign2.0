#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationSegmentsFlashing : public AnimationInterface
{
public:
    AnimationSegmentsFlashing();
    AnimationSegmentsFlashing(const QColor &color, unsigned timeOffsetBetweenSegments=20, unsigned timeToWaitFullColor = 0);
    
    bool renderFrame() override;
    virtual QString getName() override { return "SegmentsFlashing"; };
    void reset() override;

private:
    QColor color;

    unsigned counter{ 0 };
    unsigned timeOffsetBetweenSegments{ 0 };
    unsigned timeToWaitFullColor{ 0 };
};

