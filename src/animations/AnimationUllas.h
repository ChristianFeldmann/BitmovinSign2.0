#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationUllas: public AnimationInterface
{
public:
    AnimationUllas() = default;
    
    bool renderFrame() override;
    virtual QString getName() override { return "Ullas"; }
    void reset() override;

private:
    unsigned int counter{0};
};

