#include "AnimationMatrixBase.h"

#include <algorithm>

AnimationMatrixBase::AnimationMatrixBase()
{
    resetMatrix();

    calculateLedsCoord();
}

bool AnimationMatrixBase::renderFrame(Frame &frame)
{
    frame = getBlackFrame();

    bool isPlaying = renderMatrix();

    for (unsigned i = 0; i < frame.size(); ++i)
    {
        frame[i] = matrix[ledsCoord[i].x][ledsCoord[i].y];
    }

    if (!isPlaying)
    {
        resetMatrix();
    }

    return isPlaying;
}

void AnimationMatrixBase::resetMatrix()
{
    for (unsigned i = 0; i < matrixSize; ++i)
    {
        for (unsigned j = 0; j < matrixSize; ++j)
        {
            matrix[i][j] = Qt::black;
        }
    }
}

bool AnimationMatrixBase::renderMatrix()
{
    this->counter++;

    for (unsigned i = 0; i < matrixSize; ++i)
    {
        for (unsigned j = 0; j < matrixSize; ++j)
        {
            if ( i == this->counter)
            {
                int value = std::min(i*3,unsigned(255));
                matrix[i][j] = interpolateColors(BITMOVIN_BLUE, Qt::white, value / 255.0);
            }
        }
    }

    if (this->counter >= matrixSize)
    {
        this->counter = 0;    
        return false;
    }
    return true;
}

void AnimationMatrixBase::calculateLedsCoord()
{
    this->draw_lines_from_points(POINTS_BASE , LED_PARTS_BACKGROUND, matrixSize);
    this->draw_lines_from_points(POINTS_PART_L, LED_PARTS_PART_LEFT, matrixSize);
    this->draw_lines_from_points(POINTS_PART_M, LED_PARTS_PART_MIDDLE, matrixSize);
    this->draw_lines_from_points(POINTS_PART_R, LED_PARTS_PART_RIGHT, matrixSize);
}

void AnimationMatrixBase::draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor)
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

void AnimationMatrixBase::draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots)
{
    for(unsigned i = 0; i < num_of_dots; i++)
    {
        float s = float(i + 1) / (num_of_dots + 1);
        Point point;
        point.x = start.x() + (end.x() - start.x()) * s;
        point.y = start.y() + (end.y() - start.y()) * s;
        this->ledsCoord.push_back(point);
    }
}
