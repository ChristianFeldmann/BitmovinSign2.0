#pragma once

#include "../AnimationBase.h"

class AnimationImageFire : public AnimationBase
{
public:
    AnimationImageFire() = delete;
    AnimationImageFire(AnimationTreeBase *parentStack);

    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override { return AnimationState::Infinite; }

    virtual QString getName() const override { return "Fire"; };
    void reset() override;

private:

    void resetFireMatrix();
    unsigned fireMatrix[imageWidth][imageHeight];
};
