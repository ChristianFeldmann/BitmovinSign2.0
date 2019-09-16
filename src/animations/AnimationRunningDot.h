#pragma once

#include "AnimationBase.h"

class AnimationRunningDot: public AnimationBase
{
public:
    AnimationRunningDot() = delete;
    AnimationRunningDot(AnimationTreeBase *parentStack);
    
    virtual QString getName() const override { return "RunningDot"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    unsigned counter {0};
    QColor color{ Qt::red };
};
