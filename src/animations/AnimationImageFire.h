#pragma once

#include <animations/AnimationImageBase.h>

class AnimationImageFire : public AnimationImageBase
{
public:
    AnimationImageFire();

    virtual QString getName() override { return "Fire"; };
    virtual void setPropertie(QString propertyName, QString value) override;
    void reset() override;

protected:
    bool renderImage() override;

private:

    void resetFireMatrix();
    unsigned fireMatrix[imageWidth][imageHeight];
};
