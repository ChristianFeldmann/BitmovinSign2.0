#pragma once

#include "AnimationBase.h"

class AnimationImageFire : public AnimationBase
{
public:
    AnimationImageFire() = delete;
    AnimationImageFire(AnimationTreeBase *parentStack);

    virtual QString getName() const override { return "Fire"; };
    void reset() override;

private:
    virtual bool renderAnimation(Frame &frame, QImage &image) override;

    void resetFireMatrix();
    unsigned fireMatrix[imageWidth][imageHeight];
};
