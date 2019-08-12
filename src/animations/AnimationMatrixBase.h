#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

const unsigned matrixSize = 120;

class AnimationMatrixBase: public AnimationInterface
{

struct Point
{
    unsigned x;
    unsigned y;
};

public:
    AnimationMatrixBase();
    
    bool renderFrame(Frame &frame) override;

protected:

    QColor matrix[matrixSize][matrixSize];

    unsigned counter{0};

    virtual void resetMatrix();

private:

    std::vector<Point> ledsCoord;

    virtual bool renderMatrix();

    void calculateLedsCoord();

    void draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor);
    void draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots);

};
