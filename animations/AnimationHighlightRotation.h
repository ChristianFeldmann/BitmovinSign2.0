#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationHighlightRotation: public AnimationInterface
{
public:
    AnimationHighlightRotation();
    AnimationHighlightRotation(LedColor &color);
    void renderFrame(Frame &frame) override;

private:
    unsigned int rotationCounters[4] {0, 0, 0, 0};

    LedColor color;
};
