#pragma once
#include <QWidget>
#include <QPainter>
#include <QPointF>

#include <Constants.h>

class DebuggerWidget : public QWidget
{
    Q_OBJECT

public:
    DebuggerWidget(QWidget *parent = nullptr);
    void draw(Frame &frame);
    

protected:
    std::vector<QPointF> points_base = {QPointF{0.5, 0.98}, QPointF{0.03 , 0.75}, QPointF{0.03 , 0.27}, QPointF{0.5, 0.03}, QPointF{0.97, 0.27}, QPointF{0.97, 0.75}};
    std::vector<int> leds_base = LED_PARTS_BACKGROUND;
    std::vector<QPointF> points_partL = {QPointF{0.09, 0.38}, QPointF{0.29, 0.5}, QPointF{0.09, 0.64}, QPointF{0.09, 0.56}, QPointF{0.17 , 0.5}, QPointF{0.09 , 0.45}};
    std::vector<int> leds_partL = LED_PARTS_PART_LEFT;
    std::vector<QPointF> points_partM = {QPointF{0.21, 0.27}, QPointF{0.58, 0.50}, QPointF{0.21, 0.74}, QPointF{0.21, 0.61}, QPointF{0.39 , 0.5}, QPointF{0.21 , 0.40}};
    std::vector<int> leds_partM = LED_PARTS_PART_MIDDLE;
    std::vector<QPointF> points_partR = {QPointF{0.37, 0.16}, QPointF{0.93, 0.50}, QPointF{0.37, 0.85}, QPointF{0.37, 0.69}, QPointF{0.67, 0.5}, QPointF{0.37 , 0.32}};
    std::vector<int> leds_partR = LED_PARTS_PART_RIGHT; 

    void paintEvent(QPaintEvent *event) override;
    void draw_dots_line(QPainter *qp, QPointF start, QPointF end, int num_of_dots, int &counter);
    void draw_lines_from_points(QPainter *qp, std::vector<QPointF> point_list, std::vector<int> led_list, int factor, int &counter);
    void draw_points(QPainter *qp);
    Frame frame;
};