#include "AnimationUllas.h"

AnimationUllas::AnimationUllas()
{
}

bool AnimationUllas::renderFrame(Frame &frame)
{
    int count = 0;

    const QColor color1 = QColor(255, 150, 0);
    const QColor color2 = QColor(255, 0, 100);
    const QColor color3 = QColor(150, 0, 255);
    const QColor color4 = QColor(0, 150, 255);

    frame = getBlackFrame();

    double timeOffset = double(this->counter) / 250.0;
    if (this->counter % 150 < 25)
    {
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[0], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[1], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[2], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[3], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[4], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[5], color1);
    }
    else if (this->counter % 150 < 50)
    {
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[0], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[1], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[2], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[3], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[4], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[5], color2);
    }
    else if (this->counter % 150 < 75)
    {
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[0], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[1], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[2], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[3], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[4], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[5], color2);
    }
    else if (this->counter % 150 < 100)
    {
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[0], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[1], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[2], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[3], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[4], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[5], color3);
    }
    else if (this->counter % 150 < 125)
    {
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[0], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[1], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[2], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[3], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[4], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[5], color3);
    }
    else if (this->counter % 150 < 150)
    {
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[0], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[1], color3);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[2], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[3], color2);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[4], color1);
        count += setRangeOfLedToColor(frame, count, LED_PARTS_BACKGROUND[5], color1);
    }

    if (this->counter % 125 < 25)
    {
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_LEFT, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_MIDDLE, Qt::black);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_RIGHT, Qt::black);

    }
    else if (this->counter % 125 < 50)
    {
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_LEFT, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_MIDDLE, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_RIGHT, Qt::black);
    }
    else if (this->counter % 125 < 75)
    {
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_LEFT, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_MIDDLE, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_RIGHT, color4);
    }
    else if (this->counter % 125 < 100)
    {
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_LEFT, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_MIDDLE, color4);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_RIGHT, color4);
    }
    else if (this->counter % 125 < 125)
    {
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_LEFT, Qt::black);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_MIDDLE, Qt::black);
        count += setRangeOfLedToColor(frame, count, NR_LED_PART_RIGHT, Qt::black);
    }

    this->counter++;
    if (this->counter > 250)
    {
        this->counter = 0;
        return false;
    }

    return true;
}
