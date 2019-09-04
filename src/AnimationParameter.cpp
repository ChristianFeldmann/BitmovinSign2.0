#include "AnimationParameter.h"

#include <cassert>
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QLabel>
#include <QPainter>
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
        assert(this->enumComboBox == nullptr);
        this->enumComboBox = new QComboBox();
        for (auto &enumItem : this->enumValues)
        {
            this->enumComboBox->addItem(enumItem);
        }
        connect(this->enumComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AnimationParameter::onEnumComboBoxIndexChanged);
        return this->enumComboBox;
    }
    if (this->type == Int)
    {
        this->intSpinBox = new QSpinBox();
        this->intSpinBox->setValue(*this->integer);
        connect(this->intSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &AnimationParameter::onIntSpinBoxValueChanged);
        return this->intSpinBox;
    }
    if (this->type == Color)
    {
        this->colorPushButton = new QPushButton();
        this->setColorForButton();
        connect(this->colorPushButton, &QPushButton::clicked, this, &AnimationParameter::onColorButtonPressed);
        return this->colorPushButton;
    }

    return new QLabel("Error");
}

void AnimationParameter::onColorButtonPressed(bool checked)
{
    Q_UNUSED(checked);
    QColor newColor = QColorDialog::getColor(*this->color, nullptr, "Please choose a new color", QColorDialog::ShowAlphaChannel);
    if (newColor.isValid())
    {
        *this->color = newColor;
        setColorForButton();
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
    *this->integer = value;
}

void AnimationParameter::setColorForButton()
{
    QImage image(50, 50, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.fillRect(0, 0, 50, 50, *this->color);
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    QIcon ico(pixmap);
    this->colorPushButton->setIcon(ico);
}

bool AnimationParameter::appendProperty(QDomElementSign &plist) const
{
    QString typeName = this->type == Enum ? "Enum" : (this->type == Int) ? "Int" : "Color";
    QString valueString;

    if (this->type == Color)
    {
        typeName = "Color";
        valueString = this->color->name();
    }
    else if (this->type == Enum)
    {
        typeName = "Enum";
        valueString = QString("%1").arg(this->enumValues[*this->enumInt]);
    }
    else if (this->type == Int)
    {
        typeName = "Int";
        valueString = QString("%1").arg(*this->integer);
    }
    else
    {
        return false;
    }
    
    QStringPairList l;
    l.append(QStringPair("Name", this->name));
    plist.appendProperiteChild(typeName, valueString, l);

    return true;
}

bool AnimationParameter::loadFromElement(QDomElementSign &plist)
{
    if (this->name.isEmpty() || this->name != plist.attribute("Name"))
    {
        return false;
    }
    QString typeString = plist.tagName();
    QString nodeText = plist.text();
    if (typeString == "Color")
    {
        this->type = Color;
        *this->color = QColor(nodeText);
        if (!(*this->color).isValid())
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Unable to convert value to QColor.";
            return false;
        }
    }
    else if (typeString == "Enum")
    {
        this->type = Enum;
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
        this->type = Int;
        bool ok;
        *this->integer = nodeText.toInt(&ok);
        if (!ok)
        {
            qDebug() << "Unable to set property '" << this->name << "' to value '" << nodeText << "'. Unable to convert value to int.";
            return false;
        }
    }

    return true;
}