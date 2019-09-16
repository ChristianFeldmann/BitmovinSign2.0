#include "DebuggerWidget.h"

#include "SignRenderHelper.h"

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
    // Split the widget area into a 3x3 "matrix" of square spaces
    int widthHeight = std::min(this->size().width(), this->size().height());
    int wh3 = widthHeight / 3;

    for (int i = 0; i < 3; i++)
    {
        if (i < this->animationNames.size())
        {
            QRect where = QRect(0, i * wh3, wh3, wh3);
            SignRenderHelper::drawSignFromFrame(painter, where, this->renderMemory->frameMap[i]);
            DebuggerWidget::drawRect(painter, where, this->animationNames[i]);

            if (this->renderMemory->imageUsed[i])
            {
                DebuggerWidget::drawImage(painter, QRect(wh3, i * wh3, wh3, wh3), this->renderMemory->imageMap[i]);
            }
            else
            {
                DebuggerWidget::drawRect(painter, QRect(wh3, i * wh3, wh3, wh3), "", true);
            }
        }
        else
        {
            DebuggerWidget::drawRect(painter, QRect(0, i * wh3, wh3, wh3), "", true);
            DebuggerWidget::drawRect(painter, QRect(wh3, i * wh3, wh3, wh3), "", true);
        }
    }

    // Draw the output frame into the square in the right middle
    QRect where = QRect(2 * wh3, wh3, wh3, wh3);
    SignRenderHelper::drawSignFromFrame(painter, where, this->renderMemory->outputFrame);
    DebuggerWidget::drawRect(painter, where, "Output");
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
