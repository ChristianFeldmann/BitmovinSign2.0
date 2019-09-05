#pragma once

#include "AnimationBase.h"

class AnimationHighlightRotation: public AnimationBase
{
public:
    AnimationHighlightRotation() = delete;
    AnimationHighlightRotation(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "HighlightRotation"; };
    void reset() override;

private:
    float rotationCounters[4] {0, 0, 0, 0};
    float runSpeed[4]{ 1.0, 1.0, 1.0, 1.0 };

    unsigned nrStripes[4]{ 20, 4, 8, 14 };
    float stripeLength[4]{ 5, 5, 5, 5 };
    QColor color[4]{ Qt::white, Qt::white, Qt::white, Qt::white };
};
