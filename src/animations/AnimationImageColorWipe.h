#pragma once

#include <animations/AnimationImageBase.h>

class AnimationImageColorWipe : public AnimationImageBase
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

    AnimationImageColorWipe() = default;
    AnimationImageColorWipe(Direction direction, QColor color);

    virtual QString getName() override { return "ColorWipe"; };
    void reset() override;

private:
    bool renderImage() override;

    unsigned counter{ 0 };
    unsigned waitFull{ 20 };
    QColor color{ BITMOVIN_BLUE };
    Direction direction{ RANDOM };
    Direction currentDirection{ RANDOM };
};
