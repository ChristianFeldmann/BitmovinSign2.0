#pragma once

#include "common/Constants.h"

#include <QPointer>
#include <QStringList>

class Parameter : public QObject
{
    Q_OBJECT

public:
    Parameter(QObject *parent=nullptr) : QObject(parent) {};
    Parameter(QString name, QColor *color);
    Parameter(QString name, int *enumInt, QStringList enumValues);
    Parameter(QString name, int *integer);
    Parameter(QString name, unsigned *unsignedInt);
    Parameter(QString name, float *floatValue);

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
