#pragma once

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QTimer>

#include "AnimationStack.h"
#include "Constants.h"

class DebuggerWidget : public QWidget
{
    Q_OBJECT

public:
    DebuggerWidget(QWidget *parent = nullptr);
    
    void draw(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory);

protected:
    std::vector<QPointF> points_base = {QPointF{0.5, 0.98}, QPointF{0.03 , 0.75}, QPointF{0.03 , 0.27}, QPointF{0.5, 0.03}, QPointF{0.97, 0.27}, QPointF{0.97, 0.75}};
    std::vector<QPointF> points_partL = {QPointF{0.09, 0.38}, QPointF{0.29, 0.5}, QPointF{0.09, 0.64}, QPointF{0.09, 0.56}, QPointF{0.17 , 0.5}, QPointF{0.09 , 0.45}};
    std::vector<QPointF> points_partM = {QPointF{0.21, 0.27}, QPointF{0.58, 0.50}, QPointF{0.21, 0.74}, QPointF{0.21, 0.61}, QPointF{0.39 , 0.5}, QPointF{0.21 , 0.40}};
    std::vector<QPointF> points_partR = {QPointF{0.37, 0.16}, QPointF{0.93, 0.50}, QPointF{0.37, 0.85}, QPointF{0.37, 0.69}, QPointF{0.67, 0.5}, QPointF{0.37 , 0.32}};

    void paintEvent(QPaintEvent *event) override;
    static void drawDotsLine(QPainter &painter, Frame &frame, QPointF start, QPointF end, unsigned num_of_dots, int &counter);
    static void drawLinesFromPoints(QPainter &painter, QRect where, Frame &frame, std::vector<QPointF> point_list, std::vector<unsigned> led_list, int &counter);
    static void drawPoints(QPainter &painter, QRect where, Frame &frame, QString lable);
    static void drawImage(QPainter &painter, QRect where, const QImage &image);
    static void drawRect(QPainter &painter, QRect where, QString lable = "");
    
    Frame *outputFrame{ nullptr };
    RenderMemory *renderMemory{ nullptr };
    QStringList animationNames;
};
