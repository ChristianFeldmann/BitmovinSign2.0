#pragma once

#include "animation/AnimationTreeBase.h"
#include "common/Constants.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QSpinBox>
#include <QStringList>

class AnimationParameter : public QObject
{
    Q_OBJECT

public:
    AnimationParameter(QObject *parent=nullptr) : QObject(parent) {};
    AnimationParameter(QString name, QColor *color);
    AnimationParameter(QString name, int *enumInt, QStringList enumValues);
    AnimationParameter(QString name, int *integer);
    AnimationParameter(QString name, unsigned *unsignedInt);
    AnimationParameter(QString name, float *floatValue);

    QWidget *createParameterWidget();

    QString getName() { return this->name; }

    bool appendProperty(QDomElement &plist) const;
    bool loadFromElement(QDomElement &plist);

private slots:
    void onColorButtonPressed(bool checked);
    void onEnumComboBoxIndexChanged(int index);
    void onIntSpinBoxValueChanged(int value);
    void onDoubleSpinBoxValueChanged(double value);

private:
    enum Type_t
    {
        Color,
        Enum,
        Int,
        UInt,
        Float
    };

    Type_t type;

    QString name;

    QColor *color{ nullptr };
    int *enumInt{ nullptr };
    QStringList enumValues;
    int *integer{ nullptr };
    unsigned *unsignedInt{ nullptr };
    float *floatValue{ nullptr };

    QComboBox *enumComboBox{ nullptr };
    QPushButton *colorPushButton{ nullptr };
    QSpinBox *intSpinBox{ nullptr };
    QDoubleSpinBox *doubleSpinBox{ nullptr };

    void setColorForButton();
};
