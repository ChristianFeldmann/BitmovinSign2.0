#include "AnimationBase.h"

#include <cassert>
#include <QDebug>

AnimationBase::AnimationBase(AnimationTreeBase *parentStack) : 
    AnimationTreeBase(parentStack)
{
    this->calculateLedsCoord();
}

AnimationTreeBase *AnimationBase::child(int number) const
{
    Q_UNUSED(number);
    return nullptr;
}

size_t AnimationBase::childCount() const
{
    return 0;
}

int AnimationBase::childNumber(AnimationTreeBase *child) const
{
    Q_UNUSED(child);
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

bool AnimationBase::removeChildren(int pos, int rows)
{
    Q_UNUSED(pos);
    Q_UNUSED(rows);
    return false;
}

void AnimationBase::convertImageToFrame(Frame &frame, QImage &image)
{
    for (unsigned i = 0; i < frame.data.size(); ++i)
    {
        frame.data[i] = image.pixelColor(this->ledsCoord[i]);
    }
    this->imageUsed = true;
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

bool AnimationBase::savePlaylist(QDomElement &root) const
{
    QDomElement d = root.ownerDocument().createElement(this->getName());
    bool success = saveParameters(d);
    root.appendChild(d);
    return success;
}
