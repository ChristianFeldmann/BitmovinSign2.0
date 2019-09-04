#pragma once

#include "AnimationTreeBase.h"
#include "Constants.h"

#include <QComboBox>
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

    QWidget *createParameterWidget();

    QString getName() { return this->name; }

    bool appendProperty(QDomElementSign &plist) const;
    bool loadFromElement(QDomElementSign &plist);

private slots:
    void onColorButtonPressed(bool checked);
    void onEnumComboBoxIndexChanged(int index);
    void onIntSpinBoxValueChanged(int value);

private:
    enum Type_t
    {
        Color,
        Enum,
        Int
    };

    Type_t type;

    QString name;

    QColor *color{ nullptr };
    int *enumInt{ nullptr };
    QStringList enumValues;
    int *integer{ nullptr };

    QComboBox *enumComboBox{ nullptr };
    QPushButton *colorPushButton{ nullptr };
    QSpinBox *intSpinBox{ nullptr };

    void setColorForButton();
};
