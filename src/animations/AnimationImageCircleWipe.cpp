#include "AnimationImageCircleWipe.h"

#include <QPainter>
#include <cmath>

AnimationImageCircleWipe::AnimationImageCircleWipe(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("color", &this->color);
    this->addParameter("speed", &this->speed);
}

void AnimationImageCircleWipe::reset()
{
    this->counter = 0.0;
}

bool AnimationImageCircleWipe::renderFrame(Frame &frame, QImage &image)
{
    QPainter qp;
    qp.begin(&image);

    const int x = image.size().width() / 2;
    const int y = image.size().height() / 2;
    const unsigned fullRadius = unsigned(std::sqrt(x*x + y * y));

    if (this->counter >= fullRadius)
    {
        image.fill(this->color);
    }
    else
    {
        image.fill(Qt::black);
    }

    if (this->counter < fullRadius || this->counter > fullRadius + this->waitFull)
    {
        int radius;
        if (this->counter < fullRadius)
        {
            qp.setPen(this->color);
            qp.setBrush(this->color);
            radius = int(this->counter);
        }
        else
        {
            qp.setPen(Qt::black);
            qp.setBrush(Qt::black);
            radius = int(this->counter) - fullRadius - this->waitFull;
        }

        QRect centeredRect = QRect(0, 0, radius*2, radius*2);
        centeredRect.moveCenter(QPoint(x, y));
        qp.drawEllipse(centeredRect);
    }

    AnimationBase::convertImageToFrame(frame, image);
    
    this->counter += this->speed;
    if (this->counter > fullRadius * 2 + this->waitFull)
    {
        this->counter = 0.0;
    }
    return this->counter < this->speed;
}
