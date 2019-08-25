#pragma once

#include "AnimationBase.h"

class AnimationSegmentsFlashing : public AnimationBase
{
public:
    AnimationSegmentsFlashing() = delete;
    AnimationSegmentsFlashing(AnimationTreeBase *parentStack);
    
    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "SegmentsFlashing"; };
    void reset() override;

private:
    QColor color{ BITMOVIN_BLUE };

    unsigned counter{ 0 };
    int timeOffsetBetweenSegments{ 0 };
    int timeToWaitFullColor{ 0 };
};

