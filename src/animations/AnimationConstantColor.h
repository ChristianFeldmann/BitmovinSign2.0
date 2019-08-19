#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationConstantColor: public AnimationInterface
{
public:
    AnimationConstantColor();
    
    virtual QString getName() override { return "ConstantColor"; };
    bool renderFrame() override;
    virtual void setPropertie(QString propertyName, QString value) override;
    
private:
    QColor color;
};
