#pragma once

#include "AnimationBase.h"

class AnimationRainbow: public AnimationBase
{
public:
    AnimationRainbow() = delete;
    AnimationRainbow(AnimationTreeBase *parentStack);
    
    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "Rainbow"; };
    void reset() override;

private:
    unsigned int counter{ 0 };
};

