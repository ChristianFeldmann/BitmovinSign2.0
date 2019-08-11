#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationHighlightSparkling: public AnimationInterface
{
public:
    AnimationHighlightSparkling();
    AnimationHighlightSparkling(LedColor &color);
    void renderFrame(Frame &frame) override;

private:
    struct Spark
    {
        unsigned int position{ 0 };
        unsigned int counter{ 0 };
    };
    std::vector<Spark> sparks;

    unsigned getRelativeIndexWrap(unsigned int idx, int offset);

    LedColor sparkColor;
    unsigned int counter{0};
};

