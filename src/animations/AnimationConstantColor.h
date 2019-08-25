#pragma once

#include "AnimationBase.h"

class AnimationConstantColor: public AnimationBase
{
public:
    AnimationConstantColor() = delete;
    AnimationConstantColor(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "ConstantColor"; };
    
private:
    QColor color{ BITMOVIN_BLUE };
};
