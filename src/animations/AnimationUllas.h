#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationUllas: public AnimationInterface
{
public:
    AnimationUllas() = default;
    
    bool renderFrame() override;
    virtual QString getName() override { return "Ullas"; }
    virtual void setPropertie(QString propertyName, QString value) override;
    void reset() override;

private:
    unsigned int counter{0};
};

