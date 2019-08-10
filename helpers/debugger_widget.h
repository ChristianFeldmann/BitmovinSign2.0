#pragma once
#include <QWidget>
#include <QPainter>
#include <QPointF>

#include "frame.h"

class debugger_widget : public QWidget
{
    Q_OBJECT

public:
    debugger_widget(QWidget *parent = nullptr);
    void draw(Frame &frame);
    

protected:
    void paintEvent(QPaintEvent *event) override;
    void draw_dots_line(QPainter *qp, QPointF start, QPointF end, int num_of_dots, int &counter);
    void draw_lines_from_points(QPainter *qp, std::vector<QPointF> point_list, std::vector<int> led_list, int factor, int &counter);
    void draw_points(QPainter *qp);
    Frame frame;
};
