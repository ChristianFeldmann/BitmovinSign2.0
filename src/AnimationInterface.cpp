#include "AnimationInterface.h"

#include <QDebug>

AnimationParameter::AnimationParameter(QString name, QColor *color)
{ 
    this->name = name;
    this->type = Color;
    this->color = color;
};

AnimationParameter::AnimationParameter(QString name, int *enumInt, QStringList enumValues) 
{ 
    this->name = name;
    this->type = Enum;
    for (QString s : enumValues)
    {
        this->enumValues.append(s.toLower());
    }
    this->enumInt = enumInt;
};

AnimationParameter::AnimationParameter(QString name, int *integer)
{ 
    this->name = name;
    this->type = Int;
    this->integer = integer;
};

void AnimationParameter::setValue(QString value)
{
    if (this->type == Color)
    {
        *this->color = QColor(value);
        if (!(*this->color).isValid())
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << value << "'. Unable to convert value to QColor.";
        }
    }
    if (this->type == Enum)
    {
        if (this->enumValues.contains(value))
        {
            *this->enumInt = this->enumValues.indexOf(value);
        }
        qDebug() << "Unable to set property '" << this->name << "' to value '" << value << "'. Could not find the enum value.";
    }
    if (this->type == Int)
    {
        bool ok;
        *this->integer = value.toInt(&ok);
        if (!ok)
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << value << "'. Unable to convert value to int.";
        }
    }
}

void AnimationInterface::setPropertie(QString propertyName, QString value)
{
    for (auto &parameter : this->animationParameters)
    {
        if (parameter.name == propertyName)
        {
            parameter.setValue(value);
            return;
        }
    }

    qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << this->getName();
};
