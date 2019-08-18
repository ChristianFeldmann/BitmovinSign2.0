#pragma once

#include <animations/AnimationImageBase.h>

class AnimationImageFire : public AnimationImageBase
{
public:
    AnimationImageFire();

    virtual QString getName() override { return "Fire"; };
    void reset() override;

protected:
    bool renderImage() override;

private:
        
    void resetFireMatrix();
    unsigned fireMatrix[imageWidth][imageHeight];
};
