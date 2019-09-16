#include "DebuggerWidget.h"

DebuggerWidget::DebuggerWidget(QWidget *parent) : 
    QWidget(parent)
{
}

void DebuggerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (this->renderMemory == nullptr || this->animationNames.empty())
    {
        return;
    }

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    
    const QSize splitSize = this->getRenderSegmentSize();
    for (int i = 0; i < 3; i++)
    {
        QPoint renderPosition = QPoint(0, i*splitSize.width());
        QRect renderRect = QRect(renderPosition, splitSize);
        if (i < this->animationNames.size())
        {
            QSize debugSize = this->renderMemory->debuggerImageMap[i].size();
            painter.drawImage(renderPosition, this->renderMemory->debuggerImageMap[i]);
            DebuggerWidget::drawRect(painter, renderRect, this->animationNames[i]);

            renderRect.translate(splitSize.width(), 0);
            if (this->renderMemory->imageUsed[i])
            {
                DebuggerWidget::drawImage(painter, renderRect, this->renderMemory->imageMap[i]);
            }
            else
            {
                DebuggerWidget::drawRect(painter, renderRect, "", true);
            }
        }
        else
        {
            DebuggerWidget::drawRect(painter, renderRect, "", true);
            renderRect.translate(splitSize.width(), 0);
            DebuggerWidget::drawRect(painter, renderRect, "", true);
        }
    }

    // Draw the output frame into the square in the right middle
    QPoint renderPosition = QPoint(2 * splitSize.width(), splitSize.width());
    QRect renderRect = QRect(renderPosition, splitSize);
    painter.drawImage(renderPosition, this->renderMemory->debuggerOutputFrame);
    DebuggerWidget::drawRect(painter, renderRect, "Output");
    painter.end();
}

void DebuggerWidget::drawImage(QPainter &painter, QRect where, const QImage &image)
{
    painter.drawImage(where, image);

    DebuggerWidget::drawRect(painter, where);
}

void DebuggerWidget::drawRect(QPainter &painter, QRect where, QString lable, bool fillBlack)
{
    painter.setPen(Qt::white);
    painter.setBrush(fillBlack ? Qt::black : Qt::transparent);
    painter.drawRect(where);
    if (!lable.isEmpty())
    {
        painter.drawText(where, Qt::AlignLeft | Qt::AlignTop, lable);
    }
}

void DebuggerWidget::draw(QStringList animationNames, RenderMemory *renderMemory)
{
    this->renderMemory = renderMemory;
    this->animationNames = animationNames;
    this->update();
}

QSize DebuggerWidget::getRenderSegmentSize() const
{
    // Split the widget area into a 3x3 "matrix" of square spaces
    int widthHeight = std::min(this->size().width(), this->size().height());
    int wh3 = widthHeight / 3;
    return QSize(wh3, wh3);
}