#pragma once

#include "../AnimationBase.h"

class AnimationRainbow: public AnimationBase
{
public:
    AnimationRainbow() = delete;
    AnimationRainbow(AnimationTreeBase *parentStack);
    
    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override { return AnimationState::Infinite; }
    virtual QString getName() const override { return "Rainbow"; };
    void reset() override;

private:
    float speed{ 1.0 };

    float counter{ 0 };
};

