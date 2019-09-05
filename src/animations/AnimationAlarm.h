#pragma once

#include "AnimationBase.h"

class AnimationAlarm : public AnimationBase
{
public:
    AnimationAlarm() = delete;
    AnimationAlarm(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "Alarm"; };
    void reset() override;

private:
    float speed{ 1.0 };
    QColor color{ Qt::red };
    float degreeSpan{ 30 };

    float counter{ 0.0 };
};
