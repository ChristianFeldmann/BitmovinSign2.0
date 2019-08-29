#include "AnimationParameter.h"

#include <QColor>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QVariant>

AnimationParameter::AnimationParameter(QString name, QColor *color) : QObject()
{
    this->name = name;
    this->type = Color;
    this->color = color;
};

AnimationParameter::AnimationParameter(QString name, int *enumInt, QStringList enumValues) : QObject()
{
    this->name = name;
    this->type = Enum;
    for (QString s : enumValues)
    {
        this->enumValues.append(s.toLower());
    }
    this->enumInt = enumInt;
};

AnimationParameter::AnimationParameter(QString name, int *integer) : QObject()
{
    this->name = name;
    this->type = Int;
    this->integer = integer;
};

QWidget *AnimationParameter::createParameterWidget()
{
    if (this->type == Enum)
    {
        QComboBox *comboBox = new QComboBox();
        for (auto &enumItem : this->enumValues)
        {
            comboBox->addItem(enumItem);
        }
        return comboBox;
        //connect!!
    }
    if (this->type == Int)
    {
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setValue(*this->integer);
        //connect!!
    }
    return new QLabel("TESTTEST");
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
