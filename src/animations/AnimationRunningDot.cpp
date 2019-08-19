#include "AnimationRunningDot.h"

#include <QDebug>

void AnimationRunningDot::setPropertie(QString propertyName, QString value)
{
    if (propertyName.toLower() == "color")
    {
        this->color = QColor(value);
    }
    else
    {
        qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << typeid(*this).name();
    }
}

void AnimationRunningDot::reset()
{
    this->counter = 0;
}

bool AnimationRunningDot::renderFrame()
{
    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        this->frame.data[i] = (i == this->counter) ? this->color : Qt::transparent;
    }

    this->counter++;
    if (this->counter > NR_LED_TOTAL)
    {
        this->counter = 0;
    }

    return this->counter == 0;
}
