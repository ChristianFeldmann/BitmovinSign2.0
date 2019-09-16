#pragma once

#include "Frame.h"

#include <QPainter>
#include <QRect>
#include <QString>

namespace SignRenderHelper
{
    void drawSignFromFrame(QPainter &painter, QRect where, Frame &frame);
    void drawSignFromFrame(QImage &outputImage, Frame &frame);
}
