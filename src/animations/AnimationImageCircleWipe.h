#pragma once

#include "AnimationBase.h"

class AnimationImageCircleWipe : public AnimationBase
{
public:
    AnimationImageCircleWipe() = delete;
    AnimationImageCircleWipe(AnimationTreeBase *parentStack);

    virtual QString getName() const override { return "CircleWipe"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    float counter{ 0 };

    float speed{ 1.0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
};
