#pragma once

#include "Constants.h"
#include "Frame.h"

class AnimationParameter
{
public:
    AnimationParameter() = default;
    AnimationParameter(QString name, QColor *color);
    AnimationParameter(QString name, int *enumInt, QStringList enumValues);
    AnimationParameter(QString name, int *integer);

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

class AnimationInterface
{
public:
    virtual ~AnimationInterface() = default;

    // Reimplement this function and fill the LED data for the frame.
    // The function should return true if the animation ended. Some animations
    // may always return true because they don't have a specific beginning and end.
    virtual bool renderFrame() = 0;

    virtual QString getName() = 0;
    void setPropertie(QString propertieName, QString value);

    virtual void reset() {};

    Frame frame;

protected:
    std::vector<AnimationParameter> animationParameters;
};
