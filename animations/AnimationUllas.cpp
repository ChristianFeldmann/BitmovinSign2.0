#include "AnimationUllas.h"

AnimationUllas::AnimationUllas()
{
}

void AnimationUllas::renderFrame(Frame &frame)
{
    int count = 0;
    static const unsigned int ledsBackground[] = LED_PARTS_BACKGROUND;

    const LedColor color1 = LedColor(255, 150, 0);
    const LedColor color2 = LedColor(255, 0, 100);
    const LedColor color3 = LedColor(150, 0, 255);
    const LedColor color4 = LedColor(0, 150, 255);

    if (this->counter % 6 == 0)
    {
        count += frame.setRangeOfLedToColor(count, ledsBackground[0], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[1], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[2], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[3], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[4], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[5], color1);
    }
    else if (this->counter % 6 == 1)
    {
        count += frame.setRangeOfLedToColor(count, ledsBackground[0], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[1], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[2], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[3], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[4], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[5], color2);
    }
    else if (this->counter % 6 == 2)
    {
        count += frame.setRangeOfLedToColor(count, ledsBackground[0], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[1], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[2], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[3], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[4], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[5], color2);
    }
    else if (this->counter % 6 == 3)
    {
        count += frame.setRangeOfLedToColor(count, ledsBackground[0], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[1], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[2], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[3], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[4], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[5], color3);
    }
    else if (this->counter % 6 == 4)
    {
        count += frame.setRangeOfLedToColor(count, ledsBackground[0], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[1], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[2], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[3], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[4], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[5], color3);
    }
    else if (this->counter % 6 == 5)
    {
        count += frame.setRangeOfLedToColor(count, ledsBackground[0], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[1], color3);
        count += frame.setRangeOfLedToColor(count, ledsBackground[2], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[3], color2);
        count += frame.setRangeOfLedToColor(count, ledsBackground[4], color1);
        count += frame.setRangeOfLedToColor(count, ledsBackground[5], color1);
    }

    if (this->counter % 55 < 11)
    {
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_LEFT, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_MIDDLE, LedColor::black);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_RIGHT, LedColor::black);

    }
    else if (this->counter % 55 < 22)
    {
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_LEFT, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_MIDDLE, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_RIGHT, LedColor::black);
    }
    else if (this->counter % 55 < 33)
    {
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_LEFT, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_MIDDLE, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_RIGHT, color4);
    }
    else if (this->counter % 55 < 44)
    {
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_LEFT, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_MIDDLE, color4);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_RIGHT, color4);
    }
    else if (this->counter % 55 < 55)
    {
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_LEFT, LedColor::black);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_MIDDLE, LedColor::black);
        count += frame.setRangeOfLedToColor(count, NR_LED_PART_RIGHT, LedColor::black);
    }

    this->counter++;
    if (this->counter > 10000)
    {
        this->counter = 0;
    }
}
