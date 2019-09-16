#pragma once

#include "AnimationBase.h"

class AnimationSegmentsFlashing : public AnimationBase
{
public:
    AnimationSegmentsFlashing() = delete;
    AnimationSegmentsFlashing(AnimationTreeBase *parentStack);
    
    virtual QString getName() const override { return "SegmentsFlashing"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    QColor color{ BITMOVIN_BLUE };

    float counter{ 0 };

    float speed{ 1.0 };
    int timeOffsetBetweenSegments{ 50 };
    int timeToWaitFullColor{ 50 };
};

