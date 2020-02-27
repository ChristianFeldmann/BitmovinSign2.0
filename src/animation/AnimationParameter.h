#pragma once

#include "common/Constants.h"

#include <QPointer>
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

    bool appendProperty(QDomElement &plist) const;
    bool loadFromElement(QDomElement &plist);

    enum class Type
    {
        Color,
        Enum,
        Int,
        UInt,
        Float
    };

    QString name;
    Type type;

    QColor *color{ nullptr };
    int *enumInt{ nullptr };
    QStringList enumValues;
    int *integer{ nullptr };
    unsigned *unsignedInt{ nullptr };
    float *floatValue{ nullptr };

    void setEnumIndex(int index);
    void setColor(QColor value);
    void setInt(int value);
    void setFloat(float value);
};
