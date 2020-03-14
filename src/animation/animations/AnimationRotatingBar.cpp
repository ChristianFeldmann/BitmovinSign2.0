#include "AnimationRotatingBar.h"

#include <QPainter>

AnimationRotatingBar::AnimationRotatingBar(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("speed", &this->speed);
    this->addParameter("color", &this->color);
    this->addParameter("thickness", &this->thickness);
}

void AnimationRotatingBar::renderFrame(Frame &frame, QImage &image)
{
    image.fill(Qt::transparent);

    QPainter qp;
    qp.begin(&image);

    qp.setPen(this->color);
    qp.setBrush(this->color);

    QRect drawRect = image.rect();

    QRect rotatingRect;
    rotatingRect.setWidth(drawRect.width() * 1.5);
    rotatingRect.setHeight(this->thickness);
    rotatingRect.moveCenter(QPoint(0, 0));

    qp.translate(drawRect.width() * 0.5, drawRect.height() * 0.5);
    qp.rotate(this->degrees);
    qp.drawRect(rotatingRect);

    qp.end();

    AnimationBase::convertImageToFrame(frame, image);

    this->degrees += this->speed;
}

void AnimationRotatingBar::reset()
{
    this->degrees = 0.0;
}