#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationSegmentsFlashing : public AnimationInterface
{
public:
    AnimationSegmentsFlashing();
    AnimationSegmentsFlashing(const QColor &color, unsigned int timeOffsetBetweenSegments=20, unsigned int timeToWaitFullColor = 0);
    
    bool renderFrame(Frame &frame) override;
    void reset() override;

private:
    QColor color;

    unsigned int counter{ 0 };
    unsigned int timeOffsetBetweenSegments{ 0 };
    unsigned int timeToWaitFullColor{ 0 };
};

