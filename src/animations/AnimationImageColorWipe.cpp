#include "AnimationImageColorWipe.h"

#include <random>
#include <QDebug>

void AnimationImageColorWipe::setPropertie(QString propertyName, QString value)
{
    if (propertyName.toLower() == "color")
    {
        this->color = QColor(value);
    }
    else if (propertyName == "direction")
    {
        if (value.toLower() == "left_to_right")
        {
            this->direction = LEFT_TO_RIGHT;
        }
        else if (value.toLower() == "right_to_left")
        {
            this->direction = RIGHT_TO_LEFT;
        }
        else if (value.toLower() == "top_to_bottom")
        {
            this->direction = TOP_TO_BOTTOM;
        }
        else if (value.toLower() == "bottom_to_top")
        {
            this->direction = BOTTOM_TO_TOP;
        }
        else if (value.toLower() == "random")
        {
            this->direction = RANDOM;
        }
        else
        {
            qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown value for option.";
        }
    }
    else
    {
        qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << typeid(*this).name();
    }
}

void AnimationImageColorWipe::reset()
{
    this->counter = 0;
    this->direction = RANDOM;
    this->currentDirection = RANDOM;
}

bool AnimationImageColorWipe::renderImage()
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
        this->image.fill(this->color);
    }
    else
    {
        unsigned linePos = this->counter;
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
                const QColor c = (overLine ^ colorInvert) ? Qt::black : this->color;
                this->image.setPixelColor(x, y, c);
            }
        }
    }
    
    this->counter++;
    if (this->counter > sizeInDirection * 2 + this->waitFull)
    {
        this->counter = 0;
        this->currentDirection = this->direction;
    }
    return this->counter == 0;
}
