#pragma once

#include "AnimationBase.h"

class AnimationConstantColor: public AnimationBase
{
public:
    AnimationConstantColor() = delete;
    AnimationConstantColor(AnimationTreeBase *parentStack);

    virtual QString getName() const override { return "ConstantColor"; };
    
private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    QColor color{ BITMOVIN_BLUE };
};
