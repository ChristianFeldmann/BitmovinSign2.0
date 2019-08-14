#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationUllas: public AnimationInterface
{
public:
    AnimationUllas();
    
    bool renderFrame(Frame &frame) override;
    void reset() override;

private:
    void setRangeOfLedConstancColor(Frame &frame, int &start, int num_of_leds, unsigned char red, unsigned char green, unsigned char blue);
    unsigned int counter{0};
};

