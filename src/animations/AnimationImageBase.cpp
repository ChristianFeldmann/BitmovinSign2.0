#include "AnimationImageBase.h"

#include <algorithm>

AnimationImageBase::AnimationImageBase()
{
    this->image = QImage(imageSize, QImage::Format_RGB32);
    this->image.fill(Qt::black);

    this->calculateLedsCoord();
}

bool AnimationImageBase::renderFrame(Frame &frame)
{
    this->image.fill(Qt::black);

    bool isFinished = this->renderImage();

    for (unsigned i = 0; i < frame.size(); ++i)
    {
        frame[i] = this->image.pixelColor(this->ledsCoord[i]);
    }
    QColor ccdebug = this->image.pixelColor(100, 100);

    return isFinished;
}

void AnimationImageBase::calculateLedsCoord()
{
    this->draw_lines_from_points(POINTS_BASE , LED_PARTS_BACKGROUND, 120);
    this->draw_lines_from_points(POINTS_PART_L, LED_PARTS_PART_LEFT, 120);
    this->draw_lines_from_points(POINTS_PART_M, LED_PARTS_PART_MIDDLE, 120);
    this->draw_lines_from_points(POINTS_PART_R, LED_PARTS_PART_RIGHT, 120);
}

void AnimationImageBase::draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor)
{
    auto num_of_lines = point_list.size();
    for (size_t i = 0; i < num_of_lines; i++)
    {
        QPointF start = point_list[i];
        QPointF end = point_list[(i+1) % num_of_lines];
        unsigned num_of_led = led_list[i];
        this->draw_dots_line(start * factor, end * factor, num_of_led);
    }
}

void AnimationImageBase::draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots)
{
    for(unsigned i = 0; i < num_of_dots; i++)
    {
        float s = float(i + 1) / (num_of_dots + 1);
        QPoint point;
        point.setX(start.x() + (end.x() - start.x()) * s);
        point.setY(start.y() + (end.y() - start.y()) * s);
        this->ledsCoord.push_back(point);
    }
}
