#pragma once

#include "AnimationBase.h"

class AnimationAlarm : public AnimationBase
{
public:
    AnimationAlarm() = delete;
    AnimationAlarm(AnimationTreeBase *parentStack);

    virtual QString getName() const override { return "Alarm"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    float speed{ 1.0 };
    QColor color{ Qt::red };
    float degreeSpan{ 30 };

    float counter{ 0.0 };
};
