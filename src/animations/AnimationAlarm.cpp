#include "AnimationAlarm.h"

#include <QPainter>

AnimationAlarm::AnimationAlarm(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("speed", &this->speed);
    this->addParameter("color", &this->color);
    this->addParameter("span", &this->degreeSpan);
}

bool AnimationAlarm::renderFrame(Frame &frame, QImage &image)
{
    image.fill(Qt::transparent);

    QPainter qp;
    qp.begin(&image);

    qp.setPen(this->color);
    qp.setBrush(this->color);
    const int startAngle = int(this->counter * 16);
    const int degreeSpan = int(this->degreeSpan * 16);
    QRect drawRect = image.rect();
    drawRect.setLeft(drawRect.left() - 20);
    drawRect.setRight(drawRect.right() + 20);
    drawRect.setTop(drawRect.top() - 20);
    drawRect.setBottom(drawRect.bottom() + 20);
    qp.drawPie(drawRect, startAngle, degreeSpan);

    qp.end();

    AnimationBase::convertImageToFrame(frame, image);

    this->counter += this->speed;
    if (this->counter > 5760)
    {
        this->counter = 0.0;
    }
    return this->counter < this->speed;
}

void AnimationAlarm::reset()
{
    this->counter = 0.0;
}