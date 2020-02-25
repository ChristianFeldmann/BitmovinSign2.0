#pragma once

#include "AnimationBase.h"

class AnimationConstantColor: public AnimationBase
{
public:
    AnimationConstantColor() = delete;
    AnimationConstantColor(AnimationTreeBase *parentStack);

    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override { return AnimationState::Infinite; }
    virtual QString getName() const override { return "ConstantColor"; };
    
private:
    QColor color{ BITMOVIN_BLUE };
};
