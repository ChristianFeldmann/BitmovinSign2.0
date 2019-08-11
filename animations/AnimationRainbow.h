#pragma once

#include "AnimationInterface.h"
#include "../helpers/frame.h"

class AnimationRainbow: public AnimationInterface
{
public:
    AnimationRainbow();
    
    void renderFrame(Frame &frame) override;

private:
    unsigned int counter{ 0 };
};

