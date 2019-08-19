#include "AnimationImageCircleWipe.h"

#include <QPainter>
#include <QDebug>

void AnimationImageCircleWipe::setPropertie(QString propertyName, QString value)
{
    if (propertyName.toLower() == "color")
    {
        this->color = QColor(value);
    }
    else
    {
        qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << typeid(*this).name();
    }
}

void AnimationImageCircleWipe::reset()
{
    this->counter = 0;
}

bool AnimationImageCircleWipe::renderImage()
{
    QPainter qp;
    qp.begin(&this->image);

    const int x = this->image.size().width() / 2;
    const int y = this->image.size().height() / 2;
    const unsigned fullRadius = unsigned(std::sqrt(x*x + y * y));
    const bool unfill = (this->counter > fullRadius);

    if (this->counter >= fullRadius)
    {
        this->image.fill(this->color);
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
    
    this->counter++;
    if (this->counter > fullRadius * 2 + this->waitFull)
    {
        this->counter = 0;
    }
    return this->counter == 0;
}