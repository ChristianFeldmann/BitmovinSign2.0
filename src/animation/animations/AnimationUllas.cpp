#include "AnimationUllas.h"

AnimationUllas::AnimationUllas(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("speed", &this->speed);

    for (size_t i = 0; i < 5; i++)
    {
        this->addParameter(QString("Color %1").arg(i), &this->colors[i]);
    }
}

void AnimationUllas::reset()
{
    this->counter = 0.0;
}

void AnimationUllas::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);
    int count = 0;

    if (this->counter < 25)
    {
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[0], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[1], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[2], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[3], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[4], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[5], this->colors[0]);
    }
    else if (this->counter < 50)
    {
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[0], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[1], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[2], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[3], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[4], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[5], this->colors[1]);
    }
    else if (this->counter < 75)
    {
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[0], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[1], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[2], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[3], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[4], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[5], this->colors[1]);
    }
    else if (this->counter < 100)
    {
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[0], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[1], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[2], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[3], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[4], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[5], this->colors[2]);
    }
    else if (this->counter < 125)
    {
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[0], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[1], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[2], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[3], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[4], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[5], this->colors[2]);
    }
    else if (this->counter <= 150)
    {
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[0], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[1], this->colors[2]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[2], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[3], this->colors[1]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[4], this->colors[0]);
        count += frame.setRangeToColor(count, LED_PARTS_BACKGROUND[5], this->colors[0]);
    }

    if (this->counter < 25)
    {
        count += frame.setRangeToColor(count, NR_LED_PART_LEFT, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_MIDDLE, this->colors[4]);
        count += frame.setRangeToColor(count, NR_LED_PART_RIGHT, this->colors[4]);

    }
    else if (this->counter < 50)
    {
        count += frame.setRangeToColor(count, NR_LED_PART_LEFT, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_MIDDLE, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_RIGHT, this->colors[4]);
    }
    else if (this->counter < 75)
    {
        count += frame.setRangeToColor(count, NR_LED_PART_LEFT, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_MIDDLE, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_RIGHT, this->colors[3]);
    }
    else if (this->counter < 100)
    {
        count += frame.setRangeToColor(count, NR_LED_PART_LEFT, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_MIDDLE, this->colors[3]);
        count += frame.setRangeToColor(count, NR_LED_PART_RIGHT, this->colors[3]);
    }
    else if (this->counter <= 150)
    {
        count += frame.setRangeToColor(count, NR_LED_PART_LEFT, this->colors[4]);
        count += frame.setRangeToColor(count, NR_LED_PART_MIDDLE, this->colors[4]);
        count += frame.setRangeToColor(count, NR_LED_PART_RIGHT, this->colors[4]);
    }

    this->counter += this->speed;
    if (this->counter >= 150)
    {
        this->counter = 0;
    }
}
