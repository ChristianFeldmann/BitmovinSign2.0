#include "AnimationImageColorWipe.h"

#include <random>

AnimationImageColorWipe::AnimationImageColorWipe(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("color", &this->color);
    this->addParameter("direction", (int*)&this->direction, QStringList() << "LEFT_TO_RIGHT" << "RIGHT_TO_LEFT" << "TOP_TO_BOTTOM" << "BOTTOM_TO_TOP" << "RANDOM");
    this->addParameter("speed", &this->speed);
    this->addParameter("waitFull", &this->waitFull);
}

void AnimationImageColorWipe::reset()
{
    this->counter = 0.0;
    this->direction = RANDOM;
    this->currentDirection = RANDOM;
}

void AnimationImageColorWipe::renderFrame(Frame &frame, QImage &image)
{
    if (this->currentDirection == RANDOM)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> dist(0, 3);

        this->currentDirection = Direction(dist(mt));
    }

    const bool horizontal = (this->currentDirection == LEFT_TO_RIGHT || this->currentDirection == RIGHT_TO_LEFT);
    bool directionInvert = (this->currentDirection == RIGHT_TO_LEFT || this->currentDirection == BOTTOM_TO_TOP);
    const unsigned sizeInDirection = (horizontal) ? imageSize.width() : imageSize.height();
    const unsigned sizeInOtherDirection = (horizontal) ? imageSize.height() : imageSize.width();
    
    if (this->counter > sizeInDirection && this->counter < sizeInDirection + this->waitFull)
    {
        image.fill(this->color);
    }
    else
    {
        unsigned linePos = unsigned(this->counter);
        bool colorInvert = false;
        if (this->counter > sizeInDirection)
        {
            colorInvert = true;
            linePos -= sizeInDirection;
            linePos -= this->waitFull;
        }

        for (unsigned i = 0; i < sizeInDirection; i++)
        {
            for (unsigned j = 0; j < sizeInOtherDirection; j++)
            {
                const int iInverted = (directionInvert) ? sizeInDirection - 1 - i : i;
                const int x = (horizontal) ? iInverted : j;
                const int y = (horizontal) ? j : iInverted;
                bool overLine = i > linePos;
                const QColor c = (overLine ^ colorInvert) ? Qt::transparent : this->color;
                image.setPixelColor(x, y, c);
            }
        }
    }

    AnimationBase::convertImageToFrame(frame, image);
    
    this->counter += this->speed;
    if (this->counter > sizeInDirection * 2 + this->waitFull)
    {
        this->counter = 0.0;
        this->currentDirection = this->direction;
    }
}

AnimationState AnimationImageColorWipe::getState()
{
    if (this->counter < this->speed)
        return AnimationState::Running;
    return AnimationState::SwitchNow;
}
