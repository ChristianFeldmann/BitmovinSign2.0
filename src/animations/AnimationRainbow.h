#pragma once

#include "AnimationBase.h"

class AnimationRainbow: public AnimationBase
{
public:
    AnimationRainbow() = delete;
    AnimationRainbow(AnimationTreeBase *parentStack);
    
    virtual QString getName() const override { return "Rainbow"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    float speed{ 1.0 };

    float counter{ 0 };
};

