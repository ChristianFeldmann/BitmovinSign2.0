#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationConstantColor: public AnimationInterface
{
public:
    AnimationConstantColor();
    AnimationConstantColor(LedColor &color);
    
    void render_frame(Frame &frame) override;

private:
    LedColor color;
};

