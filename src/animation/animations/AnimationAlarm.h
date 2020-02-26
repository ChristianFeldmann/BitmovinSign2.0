#pragma once

#include "../AnimationBase.h"

class AnimationAlarm : public AnimationBase
{
public:
    AnimationAlarm() = delete;
    AnimationAlarm(AnimationTreeBase *parentStack);

    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override { return AnimationState::Infinite; }
    virtual QString getName() const override { return "Alarm"; };
    void reset() override;

private:
    float speed{ 1.0 };
    QColor color{ Qt::red };
    float degreeSpan{ 30 };

    float counter{ 0.0 };
};
