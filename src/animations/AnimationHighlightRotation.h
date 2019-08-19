#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationHighlightRotation: public AnimationInterface
{
public:
    AnimationHighlightRotation();
    virtual QString getName() override { return "HighlightRotation"; };
    
    bool renderFrame() override;
    void reset() override;

private:
    unsigned int rotationCounters[4] {0, 0, 0, 0};

    QColor color{ BITMOVIN_BLUE };
};
