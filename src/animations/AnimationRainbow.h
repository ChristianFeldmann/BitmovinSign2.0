#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationRainbow: public AnimationInterface
{
public:
    AnimationRainbow() = default;
    
    bool renderFrame() override;
    virtual QString getName() override { return "Rainbow"; };
    void reset() override;

private:
    unsigned int counter{ 0 };
};

