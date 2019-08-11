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
    for(int i = 0; i < num_of_dots; i++)
    {
        float s = float(i + 1) / (num_of_dots + 1);
        int x = start.x() + (end.x() - start.x()) * s;
        int y = start.y() + (end.y() - start.y()) * s;
        qp->setPen(this->frame.ledData[counter]);
        qp->setBrush(this->frame.ledData[counter]);
        qp->drawEllipse(x, y, 5, 5);
        counter++;
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

    this->draw_lines_from_points(qp, this->points_base, this->leds_base, factor, led_counter);
    this->draw_lines_from_points(qp, this->points_partL, this->leds_partL, factor, led_counter);
    this->draw_lines_from_points(qp, this->points_partM, this->leds_partM, factor, led_counter);
    this->draw_lines_from_points(qp, this->points_partR, this->leds_partR, factor, led_counter);
}

void DebuggerWidget::draw(Frame &f)
{
    this->frame.ledData = f.ledData;
    this->update();
}
