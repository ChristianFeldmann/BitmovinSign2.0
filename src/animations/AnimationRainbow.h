#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationRainbow: public AnimationInterface
{
public:
    AnimationRainbow() = default;
    
    bool renderFrame() override;
    virtual QString getName() override { return "Rainbow"; };
    virtual void setPropertie(QString propertyName, QString value) override;
    void reset() override;

private:
    unsigned int counter{ 0 };
};

