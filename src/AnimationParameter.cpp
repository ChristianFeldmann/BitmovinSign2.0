#include "AnimationParameter.h"

#include <QColor>
#include <QDebug>
#include <QVariant>

AnimationParameter::AnimationParameter(AnimationTreeBase *animation, QString name, QColor *color) :
    AnimationTreeBase(animation)
{
    this->name = name;
    this->type = Color;
    this->color = color;
};

AnimationParameter::AnimationParameter(AnimationTreeBase *animation, QString name, int *enumInt, QStringList enumValues) :
    AnimationTreeBase(animation)
{
    this->name = name;
    this->type = Enum;
    for (QString s : enumValues)
    {
        this->enumValues.append(s.toLower());
    }
    this->enumInt = enumInt;
};

AnimationParameter::AnimationParameter(AnimationTreeBase *animation, QString name, int *integer) :
    AnimationTreeBase(animation)
{
    this->name = name;
    this->type = Int;
    this->integer = integer;
};

AnimationTreeBase *AnimationParameter::child(int number)
{
    Q_UNUSED(number);
    // A parameter has no further children
    return nullptr;
}

size_t AnimationParameter::childCount() const
{
    return 0;
}

int AnimationParameter::childNumber(AnimationTreeBase *child) const
{
    Q_UNUSED(child);
    return 0;
}

QVariant AnimationParameter::data(int column) const
{
    if (column == 0)
    {
        return QVariant(this->name);
    }
    else if (column == 1)
    {
        if (this->type == Color)
        {
            return QVariant(&this->color);
        }
        if (this->type == Enum)
        {
            return QVariant(&this->enumInt);
        }
        if (type == Int)
        {
            return QVariant(&this->integer);
        }
    }

    return {};
}

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
        else
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << value << "'. Could not find the enum value.";
        }
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
