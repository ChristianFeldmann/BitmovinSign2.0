#include "AnimationMatrixFire.h"

#include <random>

std::vector<QColor> fireBase = {
    QColor(0x07,0x07,0x07),
    QColor(0x1F,0x07,0x07),
    QColor(0x2F,0x0F,0x07),
    QColor(0x47,0x0F,0x07),
    QColor(0x57,0x17,0x07),
    QColor(0x67,0x1F,0x07),
    QColor(0x77,0x1F,0x07),
    QColor(0x8F,0x27,0x07),
    QColor(0x9F,0x2F,0x07),
    QColor(0xAF,0x3F,0x07),
    QColor(0xBF,0x47,0x07),
    QColor(0xC7,0x47,0x07),
    QColor(0xDF,0x4F,0x07),
    QColor(0xDF,0x57,0x07),
    QColor(0xDF,0x57,0x07),
    QColor(0xD7,0x5F,0x07),
    QColor(0xD7,0x5F,0x07),
    QColor(0xD7,0x67,0x0F),
    QColor(0xCF,0x6F,0x0F),
    QColor(0xCF,0x77,0x0F),
    QColor(0xCF,0x7F,0x0F),
    QColor(0xCF,0x87,0x17),
    QColor(0xC7,0x87,0x17),
    QColor(0xC7,0x8F,0x17),
    QColor(0xC7,0x97,0x1F),
    QColor(0xBF,0x9F,0x1F),
    QColor(0xBF,0x9F,0x1F),
    QColor(0xBF,0xA7,0x27),
    QColor(0xBF,0xA7,0x27),
    QColor(0xBF,0xAF,0x2F),
    QColor(0xB7,0xAF,0x2F),
    QColor(0xB7,0xB7,0x2F),
    QColor(0xB7,0xB7,0x37),
    QColor(0xCF,0xCF,0x6F),
    QColor(0xDF,0xDF,0x9F),
    QColor(0xEF,0xEF,0xC7),
    QColor(0xFF,0xFF,0xFF),
};

AnimationMatrixFire::AnimationMatrixFire() : AnimationMatrixBase()
{
    resetMatrix();
}

bool AnimationMatrixFire::renderMatrix()
{
    this->counter++;

    for(unsigned i = 0 ; i < matrixSize; ++i) 
    {
        for (unsigned j = 4; j < matrixSize; ++j) 
        {
            if (fireMatrix[i][j] == 0)
            {
                fireMatrix[i][j-1] = 0;
            }
            else
            {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<double> randomNr(0, 3);

                unsigned randNumber = unsigned(randomNr(mt));

                fireMatrix[i][j - 1 - (randNumber & 1)] = fireMatrix[i][j] - (randNumber & 1);
            }
        }
    }

    for (unsigned i = 0; i < matrixSize; ++i)
    {
        for (unsigned j = 0; j < matrixSize; ++j)
        {
            unsigned index = fireMatrix[i][j];
            matrix[i][j] = fireBase[index];
        }
    }

    if (this->counter >= 250)
    {
        this->counter = 0;    
        return false;
    }
    return true;
}

void AnimationMatrixFire::resetMatrix()
{
    AnimationMatrixBase::resetMatrix();

    for (unsigned i = 0; i < matrixSize; ++i)
    {
        for (unsigned j = 0; j < matrixSize; ++j)
        {
            fireMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < matrixSize; i++)
    {
        fireMatrix[i][matrixSize-1] = unsigned(fireBase.size()) - 1;
    }
}
