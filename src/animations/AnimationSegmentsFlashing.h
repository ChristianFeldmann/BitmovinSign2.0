#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationSegmentsFlashing : public AnimationInterface
{
public:
    AnimationSegmentsFlashing() = default;
    
    bool renderFrame() override;
    virtual QString getName() override { return "SegmentsFlashing"; };
    virtual void setPropertie(QString propertyName, QString value) override;
    void reset() override;

private:
    QColor color{ BITMOVIN_BLUE };

    unsigned counter{ 0 };
    unsigned timeOffsetBetweenSegments{ 0 };
    unsigned timeToWaitFullColor{ 0 };
};

