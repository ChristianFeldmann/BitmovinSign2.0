#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationConstantColor: public AnimationInterface
{
public:
    AnimationConstantColor();
    AnimationConstantColor(Led &color);
    
    void render_frame(Frame &frame) override;

private:
    Led color;
};

