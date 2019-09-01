#include "AnimationParameter.h"

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
        //connect!!
        return this->enumComboBox;
    }
    if (this->type == Int)
    {
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setValue(*this->integer);
        //connect!!
        return spinBox;
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
