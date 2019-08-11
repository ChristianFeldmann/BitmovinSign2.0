#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationConstantColor: public AnimationInterface
{
public:
    AnimationConstantColor();
    AnimationConstantColor(QColor &color);
    
    void renderFrame(Frame &frame) override;

private:
    QColor color;
};

