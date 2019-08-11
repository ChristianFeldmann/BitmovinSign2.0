#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationConstantColor: public AnimationInterface
{
public:
    AnimationConstantColor();
    AnimationConstantColor(QColor &color);
    
    bool renderFrame(Frame &frame) override;

private:
    QColor color;
};
