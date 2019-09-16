#pragma once

#include "AnimationBase.h"

class AnimationUllas: public AnimationBase
{
public:
    AnimationUllas() = delete;
    AnimationUllas(AnimationTreeBase *parentStack);
    
    virtual QString getName() const override { return "Ullas"; }
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    float counter{ 0.0 };
    float speed{ 1.0 };

    QColor colors[5]{ QColor(255, 150, 0), QColor(255, 0, 100), QColor(150, 0, 255), QColor(0, 150, 255), QColor(0, 0, 0) };
};

