#include "AnimationConstantColor.h"

#include <QDebug>

AnimationConstantColor::AnimationConstantColor()
{
    color = BITMOVIN_BLUE;
}

void AnimationConstantColor::setPropertie(QString propertyName, QString value)
{
    if (propertyName.toLower() == "color")
    {
        this->color = QColor(value);
    }
    else
    {
        qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << typeid(*this).name();
    }
};

bool AnimationConstantColor::renderFrame()
{
    std::fill(this->frame.data.begin(), this->frame.data.end(), this->color);
    return true;
}
