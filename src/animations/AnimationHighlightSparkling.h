#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationHighlightSparkling: public AnimationInterface
{
public:
    AnimationHighlightSparkling();
    AnimationHighlightSparkling(QColor &color);
    bool renderFrame(Frame &frame) override;

private:
    struct Spark
    {
        unsigned int position{ 0 };
        unsigned int counter{ 0 };
    };
    std::vector<Spark> sparks;

    unsigned getRelativeIndexWrap(unsigned int idx, int offset);

    QColor sparkColor;
    unsigned int counter{0};
};

