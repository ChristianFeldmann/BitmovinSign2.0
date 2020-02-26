#pragma once

#include "../AnimationBase.h"

class AnimationImageCircleWipe : public AnimationBase
{
public:
    AnimationImageCircleWipe() = delete;
    AnimationImageCircleWipe(AnimationTreeBase *parentStack);

    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override;

    virtual QString getName() const override { return "CircleWipe"; };
    void reset() override;

private:
    float counter{ 0 };

    float speed{ 1.0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
};
