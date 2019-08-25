#pragma once

#include "AnimationBase.h"

class AnimationImageFire : public AnimationBase
{
public:
    AnimationImageFire() = delete;
    AnimationImageFire(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;

    virtual QString getName() const override { return "Fire"; };
    void reset() override;

private:

    void resetFireMatrix();
    unsigned fireMatrix[imageWidth][imageHeight];
};
