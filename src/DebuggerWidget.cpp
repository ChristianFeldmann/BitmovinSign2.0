#include "DebuggerWidget.h"

DebuggerWidget::DebuggerWidget(QWidget *parent): QWidget(parent)
{
   this->setGeometry(1000, 1000, 1000, 1000);
   this->setWindowTitle("Points");
   QPalette pal = palette();
   pal.setColor(QPalette::Window, Qt::black);
   this->setPalette(pal);
   this->show();
}

void DebuggerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    this->draw_points(&painter);
    painter.end();
}

void DebuggerWidget::draw_dots_line(QPainter *qp, QPointF start, QPointF end, int num_of_dots, int &counter)
{
    for(unsigned i = 0; i < num_of_dots; i++)
    {
        if (i < this->frame.size())
        {
            float s = float(i + 1) / (num_of_dots + 1);
            int x = start.x() + (end.x() - start.x()) * s;
            int y = start.y() + (end.y() - start.y()) * s;
            qp->setPen(this->frame[counter]);
            qp->setBrush(this->frame[counter]);
            qp->drawEllipse(x, y, 10, 10);
            counter++;
        }
    }
}

void DebuggerWidget::draw_lines_from_points(QPainter *qp, std::vector<QPointF> point_list, std::vector<int> led_list, int factor, int &counter)
{
    auto num_of_lines = point_list.size();
    for (size_t i = 0; i < num_of_lines; i++)
    {
        QPointF start = point_list[i];
        QPointF end = point_list[(i+1) % num_of_lines];
        int num_of_led = led_list[i];
        this->draw_dots_line(qp, start * factor, end * factor, num_of_led, counter);
    }
}

void DebuggerWidget::draw_points(QPainter *qp)
{
    int factor = std::min(this->size().width(), this->size().height());
    int led_counter = 0;

    this->draw_lines_from_points(qp, POINTS_BASE , LED_PARTS_BACKGROUND, factor, led_counter);
    this->draw_lines_from_points(qp, POINTS_PART_L, LED_PARTS_PART_LEFT, factor, led_counter);
    this->draw_lines_from_points(qp, POINTS_PART_M, LED_PARTS_PART_MIDDLE, factor, led_counter);
    this->draw_lines_from_points(qp, POINTS_PART_R, LED_PARTS_PART_RIGHT, factor, led_counter);
}

void DebuggerWidget::draw(Frame &f)
{
    this->frame = f;
    this->update();
}
