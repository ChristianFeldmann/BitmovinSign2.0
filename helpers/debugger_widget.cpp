#include "debugger_widget.h"

debugger_widget::debugger_widget(QWidget *parent): QWidget(parent)
{
   this->setGeometry(1000, 1000, 1000, 1000);
   this->setWindowTitle("Points");
   this->show();
}

void debugger_widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);
    this->draw_points(&painter);
    painter.end();
}

void debugger_widget::draw_dots_line(QPainter *qp, QPointF start, QPointF end, int num_of_dots, int counter)
{
    for(int i = 0; i < num_of_dots; i++)
    {
        float s = float(i + 1) / (num_of_dots + 1);
        int x = start.x() + (end.x() - start.x()) * s;
        int y = start.y() + (end.y() - start.y()) * s;
        // qp->setPen(QColor(this->frame.led[counter + i].red, this->frame.led[counter + i].green, this->frame.led[counter + i].blue));
        // qp->setBrush(QColor(this->frame.led[counter + i].red, this->frame.led[counter + i].green, this->frame.led[counter + i].blue));
        qp->setPen(Qt::red);
        qp->setBrush(Qt::red);
        qp->drawEllipse(x, y, 5, 5);
    }
}

void debugger_widget::draw_lines_from_points(QPainter *qp, std::vector<QPointF> point_list, std::vector<int> led_list, int factor, int &counter)
{
    int num_of_lines = point_list.size();
    for (int i = 0; i < num_of_lines; i++)
    {
        QPointF start = point_list[i];
        QPointF end = point_list[(i+1) % num_of_lines];
        int num_of_led = led_list[i];
        this->draw_dots_line(qp, start * factor, end * factor, num_of_led, counter);
    }
}

void debugger_widget::draw_points(QPainter *qp)
{
    int factor = std::min(this->size().width(), this->size().height());
    int led_counter = 0;

    this->draw_lines_from_points(qp, this->points_base, this->leds_base, factor, led_counter);
    this->draw_lines_from_points(qp, this->points_partL, this->leds_partL, factor, led_counter);
    this->draw_lines_from_points(qp, this->points_partM, this->leds_partM, factor, led_counter);
    this->draw_lines_from_points(qp, this->points_partR, this->leds_partR, factor, led_counter);
}

void debugger_widget::draw(Frame &f)
{
    this->frame.led = f.led;
    this->update();
}