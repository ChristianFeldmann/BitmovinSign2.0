#pragma once

#include <animations/AnimationImageBase.h>

class AnimationImageCircleWipe : public AnimationImageBase
{
public:
    AnimationImageCircleWipe() = default;
    AnimationImageCircleWipe(QColor color);

    virtual QString getName() override { return "CircleWipe"; };
    void reset() override;

private:
    bool renderImage() override;

    unsigned counter{ 0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
};
