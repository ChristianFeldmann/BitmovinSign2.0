#include "DebuggerWidget.h"

DebuggerWidget::DebuggerWidget(QWidget *parent) : 
    QWidget(parent)
{
}

DebuggerWidget::DebuggerWidget(DrawMode drawMode, QWidget *parent) :
    QWidget(parent)
{
    this->drawMode = drawMode;
}

void DebuggerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (this->outputFrame == nullptr)
        return;
    if (this->drawMode == DrawMode::MultipleAnimations && (this->animationNames.empty() || this->renderMemory == nullptr))
        return;

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    const int widthHeight = std::min(this->size().width(), this->size().height());

    if (this->drawMode == DrawMode::MultipleAnimations)
    {
        // Split the widget area into a 3x3 "matrix" of square spaces
        int wh3 = widthHeight / 3;

        for (int i = 0; i < 3; i++)
        {
            if (i < this->animationNames.size())
            {
                DebuggerWidget::drawPoints(painter, QRect(0, i * wh3, wh3, wh3), this->renderMemory->frameMap[i], this->animationNames[i]);
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
        DebuggerWidget::drawPoints(painter, QRect(2 * wh3, wh3, wh3, wh3), *this->outputFrame, "Output");
    }
    else
    {

        DebuggerWidget::drawPoints(painter, QRect(0, 0, widthHeight, widthHeight), *this->outputFrame, "Output");
    }
    
    painter.end();
}

void DebuggerWidget::drawDotsLine(QPainter &painter, Frame &frame, QPointF start, QPointF end, unsigned num_of_dots, int &counter, int radius)
{
    auto &data = frame.data;
    for(unsigned i = 0; i < num_of_dots; i++)
    {
        if (i < data.size())
        {
            float s = float(i + 1) / (num_of_dots + 1);
            int x = start.x() + (end.x() - start.x()) * s;
            int y = start.y() + (end.y() - start.y()) * s;
            painter.setPen(data[counter]);
            painter.setBrush(data[counter]);
            painter.drawEllipse(x, y, radius, radius);
            counter++;
        }
    }
}

void DebuggerWidget::drawLinesFromPoints(QPainter &painter, QRect where, Frame &frame, std::vector<QPointF> point_list, std::vector<unsigned> led_list, int &counter, int radius)
{
    auto num_of_lines = point_list.size();
    for (size_t i = 0; i < num_of_lines; i++)
    {
        QPointF startRelative = point_list[i];
        QPointF endRelative = point_list[(i+1) % num_of_lines];
        
        QPointF start = where.topLeft() + startRelative * where.width();
        QPointF end = where.topLeft() + endRelative * where.width();

        unsigned num_of_led = led_list[i];
        DebuggerWidget::drawDotsLine(painter, frame, start, end, num_of_led, counter, radius);
    }
}

void DebuggerWidget::drawPoints(QPainter &painter, QRect where, Frame &frame, QString lable)
{
    int led_counter = 0;

    int radius = std::max(1, where.width() / 70);

    DebuggerWidget::drawLinesFromPoints(painter, where, frame, POINTS_BASE , LED_PARTS_BACKGROUND, led_counter, radius);
    DebuggerWidget::drawLinesFromPoints(painter, where, frame, POINTS_PART_L, LED_PARTS_PART_LEFT, led_counter, radius);
    DebuggerWidget::drawLinesFromPoints(painter, where, frame, POINTS_PART_M, LED_PARTS_PART_MIDDLE, led_counter, radius);
    DebuggerWidget::drawLinesFromPoints(painter, where, frame, POINTS_PART_R, LED_PARTS_PART_RIGHT, led_counter, radius);

    DebuggerWidget::drawRect(painter, where, lable);
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

void DebuggerWidget::draw(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory)
{
    this->outputFrame = outputFrame;
    this->renderMemory = renderMemory;
    this->animationNames = animationNames;
    this->update();
}
