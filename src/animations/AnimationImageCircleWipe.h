#pragma once

#include <animations/AnimationImageBase.h>

class AnimationImageCircleWipe : public AnimationImageBase
{
public:
    AnimationImageCircleWipe() = default;

    virtual QString getName() override { return "CircleWipe"; };
    virtual void setPropertie(QString propertyName, QString value) override;
    void reset() override;

private:
    bool renderImage() override;

    unsigned counter{ 0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
};
