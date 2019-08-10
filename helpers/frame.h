#pragma once
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

#include <QImage>

#define TOTAL_LEDS 489

struct Led
{
    /* data */
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};


class Frame
{
public: 
    std::vector<QPointF> points_base = {QPointF{0.5, 0.98}, QPointF{0.03 , 0.75}, QPointF{0.03 , 0.27}, QPointF{0.5, 0.03}, QPointF{0.97, 0.27}, QPointF{0.97, 0.75}};
    std::vector<int> leds_base = {34, 36, 33, 34, 35, 34};
    std::vector<QPointF> points_partL = {QPointF{0.09, 0.38}, QPointF{0.29, 0.5}, QPointF{0.09, 0.64}, QPointF{0.09, 0.56}, QPointF{0.17 , 0.5}, QPointF{0.09 , 0.45}};
    std::vector<int> leds_partL = {14, 14, 2, 7, 7, 2};
    std::vector<QPointF> points_partM = {QPointF{0.21, 0.27}, QPointF{0.58, 0.50}, QPointF{0.21, 0.74}, QPointF{0.21, 0.61}, QPointF{0.39 , 0.5}, QPointF{0.21 , 0.40}};
    std::vector<int> leds_partM = {26, 26, 5, 14, 14, 5};
    std::vector<QPointF> points_partR = {QPointF{0.37, 0.16}, QPointF{0.93, 0.50}, QPointF{0.37, 0.85}, QPointF{0.37, 0.69}, QPointF{0.67, 0.5}, QPointF{0.37 , 0.32}};
    std::vector<int> leds_partR = {42, 41, 8, 24, 24, 8};   
    Frame(/* args */) {led = std::vector<Led>(TOTAL_LEDS);};
    ~Frame() {};
    std::vector<Led> led;

    void convertImageToByteArray() {};

private:
    QImage image;
};