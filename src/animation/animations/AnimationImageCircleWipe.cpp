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

void AnimationImageCircleWipe::renderFrame(Frame &frame, QImage &image)
{
    const int x = image.size().width() / 2;
    const int y = image.size().height() / 2;
    const unsigned fullRadius = unsigned(std::sqrt(x*x + y * y));

    if (this->counter >= fullRadius)
    {
        image.fill(this->color);
    }
    else
    {
        image.fill(Qt::transparent);
    }

    QPainter qp;
    qp.begin(&image);
    qp.setCompositionMode(QPainter::CompositionMode_Source);

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
            qp.setPen(Qt::transparent);
            qp.setBrush(Qt::transparent);
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
}

AnimationState AnimationImageCircleWipe::getState()
{
    if (this->counter < this->speed)
        return AnimationState::Running;
    return AnimationState::SwitchNow;
}
