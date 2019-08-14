#include "DebuggerWidget.h"

#include <QDebug>

DebuggerWidget::DebuggerWidget(QWidget *parent): QWidget(parent)
{
    this->resize(1000, 500);
    this->setWindowTitle("Points");
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    this->setPalette(pal);

    connect(&this->fpsTimer, &QTimer::timeout, this, &DebuggerWidget::fpsTimerTimeout);
    this->fpsTimer.start(1000);

    this->show();
}

void DebuggerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    this->draw_points(&painter);
    if (this->animationImage)
    {
        const QImage &img = this->animationImage->getImage();
        const QSize imageSize = img.size();
        int imageDrawWidth = std::min(this->size().width() / 2, this->size().height());
        int imageDrawHeight = imageDrawWidth * imageSize.width() / imageSize.height();

        QRect target = QRect(this->size().width() / 2, 0, imageDrawWidth, imageDrawHeight);
        painter.drawImage(target, img);
    }
    // Draw the fps text
    painter.setPen(Qt::white);
    painter.drawText(5, 10, QString::number(this->currentFps));
    painter.end();

    this->fpsDrawCounter++;
}

void DebuggerWidget::fpsTimerTimeout()
{
    this->currentFps = this->fpsDrawCounter;
    this->fpsDrawCounter = 0;
}

void DebuggerWidget::draw_dots_line(QPainter *qp, QPointF start, QPointF end, unsigned num_of_dots, int &counter)
{
    for(unsigned i = 0; i < num_of_dots; i++)
    {
        if (i < this->frame.size())
        {
            float s = float(i + 1) / (num_of_dots + 1);
            int x = start.x() + (end.x() - start.x()) * s;
            int y = start.y() + (end.y() - start.y()) * s;
            qp->setPen(this->frame[counter]);
            qp->setBrush(this->frame[counter]);
            qp->drawEllipse(x, y, 10, 10);
            counter++;
        }
    }
}

void DebuggerWidget::draw_lines_from_points(QPainter *qp, std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor, int &counter)
{
    auto num_of_lines = point_list.size();
    for (size_t i = 0; i < num_of_lines; i++)
    {
        QPointF start = point_list[i];
        QPointF end = point_list[(i+1) % num_of_lines];
        unsigned num_of_led = led_list[i];
        this->draw_dots_line(qp, start * factor, end * factor, num_of_led, counter);
    }
}

void DebuggerWidget::draw_points(QPainter *qp)
{
    int factor = std::min(this->size().width() / 2, this->size().height());
    int led_counter = 0;

    this->draw_lines_from_points(qp, POINTS_BASE , LED_PARTS_BACKGROUND, factor, led_counter);
    this->draw_lines_from_points(qp, POINTS_PART_L, LED_PARTS_PART_LEFT, factor, led_counter);
    this->draw_lines_from_points(qp, POINTS_PART_M, LED_PARTS_PART_MIDDLE, factor, led_counter);
    this->draw_lines_from_points(qp, POINTS_PART_R, LED_PARTS_PART_RIGHT, factor, led_counter);
}

void DebuggerWidget::draw(Frame &f, std::shared_ptr<AnimationImageBase> animationImage)
{
    this->frame = f;
    this->animationImage = animationImage;
    this->update();
}
