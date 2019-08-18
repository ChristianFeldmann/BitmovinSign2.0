#pragma once

#include "Constants.h"
#include "Frame.h"

class AnimationInterface
{
public:
    virtual ~AnimationInterface() = default;

    // Reimplement this function and fill the LED data for the frame.
    // The function should return true if the animation ended. Some animations
    // may always return true because they don't have a specific beginning and end.
    virtual bool renderFrame() = 0;

    virtual QString getName() = 0;

    virtual void reset() {};

    Frame frame;
};
