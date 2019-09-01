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

    void setValue(QString value);
    QString getName() { return this->name; }

private slots:
    void onColorButtonPressed(bool checked);

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
