#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationRunningDot: public AnimationInterface
{
public:
    AnimationRunningDot() = default;
    
    bool renderFrame() override;
    virtual QString getName() override { return "RunningDot"; };
    virtual void setPropertie(QString propertyName, QString value) override;
    void reset() override;

private:
    unsigned counter {0};
    QColor color{ Qt::red };
};
