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
    unsigned int rotationCounters[4] {0, 0, 0, 0};

    QColor color{ BITMOVIN_BLUE };
};
