#include "SignRenderHelper.h"

namespace SignRenderHelper
{
    void drawDotsLine(QPainter &painter, Frame &frame, QPointF start, QPointF end, unsigned num_of_dots, int &counter, int radius)
    {
        auto &data = frame.data;
        for (unsigned i = 0; i < num_of_dots; i++)
        {
            if (i < data.size())
            {
                float s = float(i + 1) / (num_of_dots + 1);
                int x = start.x() + (end.x() - start.x()) * s;
                int y = start.y() + (end.y() - start.y()) * s;
                painter.setPen(data[counter]);
                painter.setBrush(data[counter]);
                //painter.drawEllipse(x, y, radius, radius);
                painter.drawRect(x, y, radius, radius);
                counter++;
            }
        }
    }

    void drawLinesFromPoints(QPainter &painter, QRect where, Frame &frame, std::vector<QPointF> point_list, std::vector<unsigned> led_list, int &counter, int radius)
    {
        auto num_of_lines = point_list.size();
        for (size_t i = 0; i < num_of_lines; i++)
        {
            QPointF startRelative = point_list[i];
            QPointF endRelative = point_list[(i + 1) % num_of_lines];

            QPointF start = where.topLeft() + startRelative * where.width();
            QPointF end = where.topLeft() + endRelative * where.width();

            unsigned num_of_led = led_list[i];
            drawDotsLine(painter, frame, start, end, num_of_led, counter, radius);
        }
    }

    void drawSignFromFrame(QPainter &painter, QRect where, Frame &frame)
    {
        int led_counter = 0;

        int radius = std::max(1, where.width() / 70);

        drawLinesFromPoints(painter, where, frame, POINTS_BASE, LED_PARTS_BACKGROUND, led_counter, radius);
        drawLinesFromPoints(painter, where, frame, POINTS_PART_L, LED_PARTS_PART_LEFT, led_counter, radius);
        drawLinesFromPoints(painter, where, frame, POINTS_PART_M, LED_PARTS_PART_MIDDLE, led_counter, radius);
        drawLinesFromPoints(painter, where, frame, POINTS_PART_R, LED_PARTS_PART_RIGHT, led_counter, radius);
    }
}
