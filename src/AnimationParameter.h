#pragma once

#include "AnimationTreeBase.h"
#include "Constants.h"

#include <QStringList>

class AnimationParameter : public AnimationTreeBase
{
public:
    AnimationParameter() = delete;
    AnimationParameter(AnimationTreeBase *animation, QString name, QColor *color);
    AnimationParameter(AnimationTreeBase *animation, QString name, int *enumInt, QStringList enumValues);
    AnimationParameter(AnimationTreeBase *animation, QString name, int *integer);

    // Overrides from the AnimationTreeBase
    AnimationTreeBase *child(int number) override;
    size_t childCount() const override;
    int childNumber(AnimationTreeBase *child) const override;
    QVariant data(int column) const override;

    void setValue(QString value);

    QString name;

private:
    enum Type_t
    {
        Color,
        Enum,
        Int
    };

    Type_t type;

    QColor *color{ nullptr };
    int *enumInt{ nullptr };
    QStringList enumValues;
    int *integer{ nullptr };
};
