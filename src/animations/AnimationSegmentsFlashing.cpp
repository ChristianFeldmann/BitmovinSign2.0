#include "AnimationSegmentsFlashing.h"

#include <QDebug>

void AnimationSegmentsFlashing::setPropertie(QString propertyName, QString value)
{
    if (propertyName.toLower() == "color")
    {
        this->color = QColor(value);
    }
    else if (propertyName.toLower() == "timeoffsetbetweensegments")
    {
        this->timeOffsetBetweenSegments = value.toInt();
    }
    else if (propertyName.toLower() == "timetowaitfullcolor")
    {
        this->timeToWaitFullColor = value.toInt();
    }
    else
    {
        qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << typeid(*this).name();
    }
}

void AnimationSegmentsFlashing::reset()
{
    this->counter = 0;
}

bool AnimationSegmentsFlashing::renderFrame()
{
    for (int i = 0; i < 4; i++)
    {
        unsigned partCounter = this->counter - this->timeOffsetBetweenSegments * i;
        if (partCounter > 0 && partCounter < 100 + this->timeToWaitFullColor)
        {
            double intensity = 0;
            if (partCounter < 50)
            {
                intensity = double(partCounter) / 50.0;
            }
            else if (partCounter < 50 + this->timeToWaitFullColor)
            {
                intensity = 1;
            }
            else
            {
                intensity = double(100 + this->timeToWaitFullColor - partCounter) / 50;
            }
            QColor c = this->color;
            c.setAlpha(int(intensity * 255));
            frame.setRangeToColor(OFFSET_LIST[i], NR_LED_LIST[i], c);
        }
    }

    this->counter++;
    const unsigned animationDuration = 100 + this->timeToWaitFullColor + 4 * this->timeOffsetBetweenSegments;
    if (this->counter > animationDuration)
    {
        this->counter = 0;
        return true;
    }

    return false;
}
