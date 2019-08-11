#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationHighlightRotation: public AnimationInterface
{
public:
    AnimationHighlightRotation();
    AnimationHighlightRotation(QColor &color);
    bool renderFrame(Frame &frame) override;

private:
    unsigned int rotationCounters[4] {0, 0, 0, 0};

    QColor color;

    unsigned counter {0};
};
