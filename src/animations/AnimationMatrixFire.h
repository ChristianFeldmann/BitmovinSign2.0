#pragma once

#include <animations/AnimationMatrixBase.h>

class AnimationMatrixFire : public AnimationMatrixBase
{
public:
    AnimationMatrixFire();

private:

    bool renderMatrix() override;

    void resetMatrix() override;

    unsigned fireMatrix[matrixSize][matrixSize];
};
