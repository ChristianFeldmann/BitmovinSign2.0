#pragma once

#include "AnimationBase.h"

class AnimationUllas: public AnimationBase
{
public:
    AnimationUllas() = delete;
    AnimationUllas(AnimationTreeBase *parentStack);
    
    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "Ullas"; }
    void reset() override;

private:
    unsigned int counter{0};
};

