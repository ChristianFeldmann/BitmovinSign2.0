#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationRainbow: public AnimationInterface
{
public:
    AnimationRainbow();
    
    bool renderFrame(Frame &frame) override;

private:
    unsigned int counter{ 0 };
};

