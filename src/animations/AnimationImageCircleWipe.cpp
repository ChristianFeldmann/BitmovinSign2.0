#include "AnimationImageCircleWipe.h"

#include <QPainter>
#include <cmath>

AnimationImageCircleWipe::AnimationImageCircleWipe(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->animationParameters.push_back(std::make_shared<AnimationParameter>("color", &this->color));
}

void AnimationImageCircleWipe::reset()
{
    this->counter = 0;
}

bool AnimationImageCircleWipe::renderFrame(Frame &frame, QImage &image)
{
    QPainter qp;
    qp.begin(&image);

    const int x = image.size().width() / 2;
    const int y = image.size().height() / 2;
    const unsigned fullRadius = unsigned(std::sqrt(x*x + y * y));
    const bool unfill = (this->counter > fullRadius);

    if (this->counter >= fullRadius)
    {
        image.fill(this->color);
    }

    if (this->counter < fullRadius || this->counter > fullRadius + this->waitFull)
    {
        int radius;
        if (this->counter < fullRadius)
        {
            qp.setPen(this->color);
            qp.setBrush(this->color);
            radius = this->counter;
        }
        else
        {
            qp.setPen(Qt::black);
            qp.setBrush(Qt::black);
            radius = this->counter - fullRadius - this->waitFull;
        }

        QRect centeredRect = QRect(0, 0, radius*2, radius*2);
        centeredRect.moveCenter(QPoint(x, y));
        qp.drawEllipse(centeredRect);
    }

    AnimationBase::convertImageToFrame(frame, image);
    
    this->counter++;
    if (this->counter > fullRadius * 2 + this->waitFull)
    {
        this->counter = 0;
    }
    return this->counter == 0;
}
