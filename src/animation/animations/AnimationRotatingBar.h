#pragma once

#include "../AnimationBase.h"

class AnimationRotatingBar : public AnimationBase
{
public:
    AnimationRotatingBar() = delete;
    AnimationRotatingBar(AnimationTreeBase *parentStack);

    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override { return AnimationState::Infinite; }
    virtual QString getName() const override { return "Rotating Bar"; };
    void reset() override;

private:
    float speed{ 1.0 };
    QColor color{ Qt::red };
    float thickness{ 30 };

    float degrees{ 0.0 };
};
