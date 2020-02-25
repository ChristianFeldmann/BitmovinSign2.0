#pragma once

#include "AnimationBase.h"

class AnimationRunningDot: public AnimationBase
{
public:
    AnimationRunningDot() = delete;
    AnimationRunningDot(AnimationTreeBase *parentStack);
    
    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override;
    virtual QString getName() const override { return "RunningDot"; };
    void reset() override;

private:
    unsigned counter {0};
    QColor color{ Qt::red };
};
