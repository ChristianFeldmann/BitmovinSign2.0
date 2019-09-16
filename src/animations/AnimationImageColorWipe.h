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

    virtual QString getName() const override { return "ColorWipe"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    float counter{ 0.0 };
    Direction currentDirection{ RANDOM };

    QColor color{ BITMOVIN_BLUE };
    Direction direction{ RANDOM };
    unsigned waitFull{ 20 };
    float speed{ 1.0 };
};
