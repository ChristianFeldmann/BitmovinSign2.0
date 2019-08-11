#include "AnimationRainbow.h"

#include <QDebug>

AnimationRainbow::AnimationRainbow()
{
}

void AnimationRainbow::renderFrame(Frame &frame)
{
    auto getColorForPos = [](double pos) -> LedColor
    {
        unsigned int posScaled = (unsigned int)(pos * 255);
        if (posScaled < 85)
        {
            return LedColor(posScaled * 3, 255 - posScaled * 3, 0);
        }
        else if (posScaled < 170)
        {
            posScaled -= 85;
            return LedColor(255 - posScaled * 3, 0, posScaled * 3);
        }
        else
        {
            posScaled -= 170;
            return LedColor(0, posScaled * 3, 255 - posScaled);
        }
    };

    const unsigned int ledOffsets[] = OFFSET_LIST;
    const unsigned int ledNrs[] = NR_LED_LIST;

    for (unsigned int j = 0; j < 4; j++)
    {
        double timeOffset = double(this->counter) / 250.0;

        for (unsigned int i = 0; i < ledNrs[j]; i++)
        {
            unsigned int timeOffsetInArray = (unsigned int)(timeOffset * ledNrs[j]);
            unsigned int idx = ledOffsets[j] + ((i + timeOffsetInArray) % ledNrs[j]);
            double pos = double(i) / ledNrs[j];
            auto c = getColorForPos(pos);
            frame.ledData[idx] = getColorForPos(pos);
        }
    }

    this->counter++;
    if (this->counter > 250)
        this->counter = 0;
}
