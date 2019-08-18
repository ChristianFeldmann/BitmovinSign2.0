#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationConstantColor: public AnimationInterface
{
public:
    AnimationConstantColor();
    AnimationConstantColor(QColor &color);
    
    virtual QString getName() override { return "ConstantColor"; };
    bool renderFrame() override;

private:
    QColor color;
};
