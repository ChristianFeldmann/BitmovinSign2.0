#pragma once

#include <AnimationInterface.h>
#include <Frame.h>

class AnimationHighlightRotation: public AnimationInterface
{
public:
    AnimationHighlightRotation();
    AnimationHighlightRotation(QColor &color);
    void renderFrame(Frame &frame) override;

private:
    unsigned int rotationCounters[4] {0, 0, 0, 0};

    QColor color;
};

