#include "AnimationBase.h"

#include <QDebug>

AnimationBase::AnimationBase(AnimationTreeBase *parentStack) : 
    AnimationTreeBase(parentStack)
{
    this->calculateLedsCoord();
}

AnimationTreeBase *AnimationBase::child(int number)
{
    if (number >= 0 && number < this->animationParameters.size())
    {
        return &this->animationParameters[number];
    }
    return nullptr;
}

size_t AnimationBase::childCount() const
{
    return this->animationParameters.size();
}

int AnimationBase::childNumber(AnimationTreeBase *child) const
{
    for (size_t i = 0; i < this->animationParameters.size(); i++)
    {
        if (&this->animationParameters[i] == child)
        {
            return int(i);
        }
    }
    return -1;
}

QVariant AnimationBase::data(int column) const
{
    if (column == 0)
    {
        return QVariant(this->getName());
    }

    return {};
}

void AnimationBase::setPropertie(QString propertyName, QString value)
{
    for (auto &parameter : this->animationParameters)
    {
        if (parameter.name == propertyName)
        {
            parameter.setValue(value);
            return;
        }
    }

    qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << this->getName();
};

void AnimationBase::convertImageToFrame(Frame &frame, QImage &image)
{
    for (unsigned i = 0; i < frame.data.size(); ++i)
    {
        frame.data[i] = image.pixelColor(this->ledsCoord[i]);
    }
}

void AnimationBase::calculateLedsCoord()
{
    this->draw_lines_from_points(POINTS_BASE, LED_PARTS_BACKGROUND, 120);
    this->draw_lines_from_points(POINTS_PART_L, LED_PARTS_PART_LEFT, 120);
    this->draw_lines_from_points(POINTS_PART_M, LED_PARTS_PART_MIDDLE, 120);
    this->draw_lines_from_points(POINTS_PART_R, LED_PARTS_PART_RIGHT, 120);
}

void AnimationBase::draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor)
{
    auto num_of_lines = point_list.size();
    for (size_t i = 0; i < num_of_lines; i++)
    {
        QPointF start = point_list[i];
        QPointF end = point_list[(i + 1) % num_of_lines];
        unsigned num_of_led = led_list[i];
        this->draw_dots_line(start * factor, end * factor, num_of_led);
    }
}

void AnimationBase::draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots)
{
    for (unsigned i = 0; i < num_of_dots; i++)
    {
        float s = float(i + 1) / (num_of_dots + 1);
        QPoint point;
        point.setX(start.x() + (end.x() - start.x()) * s);
        point.setY(start.y() + (end.y() - start.y()) * s);
        this->ledsCoord.push_back(point);
    }
}