#pragma once

#include "AnimationBase.h"

class AnimationImageCircleWipe : public AnimationBase
{
public:
    AnimationImageCircleWipe() = delete;
    AnimationImageCircleWipe(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;

    virtual QString getName() const override { return "CircleWipe"; };
    void reset() override;

private:

    unsigned counter{ 0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
};
