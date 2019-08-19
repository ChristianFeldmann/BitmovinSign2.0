#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationRunningDot: public AnimationInterface
{
public:
    AnimationRunningDot();
    
    bool renderFrame() override;
    virtual QString getName() override { return "RunningDot"; };
    void reset() override;

private:
    unsigned counter {0};
    QColor color{ Qt::red };
};
