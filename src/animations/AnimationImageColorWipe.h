#pragma once

#include "AnimationBase.h"

class AnimationImageColorWipe : public AnimationBase
{
public:
    enum Direction
    {
        LEFT_TO_RIGHT,
        RIGHT_TO_LEFT,
        TOP_TO_BOTTOM,
        BOTTOM_TO_TOP,
        RANDOM
    };

    AnimationImageColorWipe() = delete;
    AnimationImageColorWipe(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;

    virtual QString getName() const override { return "ColorWipe"; };
    void reset() override;

private:
    unsigned counter{ 0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
    Direction direction{ RANDOM };
    Direction currentDirection{ RANDOM };
};
