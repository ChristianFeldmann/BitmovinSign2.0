#include "AnimationParameter.h"

#include <cassert>
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QPainter>
#include <QVariant>

AnimationParameter::AnimationParameter(QString name, QColor *color) : QObject()
{
    this->name = name;
    this->type = Type::Color;
    this->color = color;
};

AnimationParameter::AnimationParameter(QString name, int *enumInt, QStringList enumValues) : QObject()
{
    this->name = name;
    this->type = Type::Enum;
    for (QString s : enumValues)
    {
        this->enumValues.append(s.toLower());
    }
    this->enumInt = enumInt;
};

AnimationParameter::AnimationParameter(QString name, int *integer) : QObject()
{
    this->name = name;
    this->type = Type::Int;
    this->integer = integer;
};

AnimationParameter::AnimationParameter(QString name, unsigned *unsignedInt) : QObject()
{
    this->name = name;
    this->type = Type::UInt;
    this->unsignedInt = unsignedInt;
};

AnimationParameter::AnimationParameter(QString name, float *floatValue) : QObject()
{
    this->name = name;
    this->type = Type::Float;
    this->floatValue = floatValue;
}

void AnimationParameter::onColorButtonPressed(bool checked)
{
    Q_UNUSED(checked);
    QColor newColor = QColorDialog::getColor(*this->color, nullptr, "Please choose a new color", QColorDialog::ShowAlphaChannel);
    if (newColor.isValid())
    {
        *this->color = newColor;
        //setColorForButton();
    }
}

void AnimationParameter::onEnumComboBoxIndexChanged(int index)
{
    if (index >= 0 && index < enumValues.count())
    {
        *this->enumInt = index;
    }
}

void AnimationParameter::onIntSpinBoxValueChanged(int value)
{
    if (this->type == Type::Int)
    {
        *this->integer = value;
    }
    else if (this->type == Type::UInt)
    {
        *this->unsignedInt = unsigned(value);
    }
    else
    {
        assert(false);
    }
}

void AnimationParameter::onDoubleSpinBoxValueChanged(double value)
{
    *this->floatValue = float(value);
}

bool AnimationParameter::appendProperty(QDomElement &plist) const
{
    QString typeName = this->type == Type::Enum ? "Enum" : (this->type == Type::Int) ? "Int" : "Color";
    QString valueString;

    if (this->type == Type::Color)
    {
        typeName = "Color";
        valueString = this->color->name();
    }
    else if (this->type == Type::Enum)
    {
        typeName = "Enum";
        valueString = QString("%1").arg(this->enumValues[*this->enumInt]);
    }
    else if (this->type == Type::Int)
    {
        typeName = "Int";
        valueString = QString("%1").arg(*this->integer);
    }
    else if (this->type == Type::UInt)
    {
        typeName = "UInt";
        valueString = QString("%1").arg(*this->unsignedInt);
    }
    else if (this->type == Type::Float)
    {
        typeName = "Float";
        valueString = QString("%1").arg(*this->floatValue);
    }
    else
    {
        return false;
    }

    QDomElement newChild = plist.ownerDocument().createElement(typeName);
    newChild.appendChild(plist.ownerDocument().createTextNode(valueString));
    newChild.setAttribute("Name", this->name);
    plist.appendChild(newChild);

    return true;
}

bool AnimationParameter::loadFromElement(QDomElement &plist)
{
    if (this->name.isEmpty() || this->name != plist.attribute("Name"))
    {
        return false;
    }
    QString typeString = plist.tagName();
    QString nodeText = plist.text();
    if (typeString == "Color")
    {
        this->type = Type::Color;
        *this->color = QColor(nodeText);
        if (!(*this->color).isValid())
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Unable to convert value to QColor.";
            return false;
        }
    }
    else if (typeString == "Enum")
    {
        this->type = Type::Enum;
        if (this->enumValues.contains(nodeText))
        {
            *this->enumInt = this->enumValues.indexOf(nodeText);
        }
        else
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Could not find the enum value.";
            return false;
        }
    }
    else if (typeString == "Int")
    {
        this->type = Type::Int;
        bool ok;
        *this->integer = nodeText.toInt(&ok);
        if (!ok)
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Unable to convert value to int.";
            return false;
        }
    }
    else if (typeString == "UInt")
    {
        this->type = Type::UInt;
        bool ok;
        *this->unsignedInt = unsigned(nodeText.toInt(&ok));
        if (!ok)
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Unable to convert value to unsigned int.";
            return false;
        }
    }
    else if (typeString == "Float")
    {
        this->type = Type::Float;
        bool ok;
        *this->floatValue = nodeText.toFloat(&ok);
        if (!ok)
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Unable to convert value to float.";
            return false;
        }
    }

    return true;
}