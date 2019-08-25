#include "AnimationRainbow.h"

AnimationRainbow::AnimationRainbow(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
}

void AnimationRainbow::reset()
{
    this->counter = 0;
}

bool AnimationRainbow::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);
    auto getColorForPos = [](double pos) -> QColor
    {
        unsigned int posScaled = (unsigned int)(pos * 255);
        if (posScaled < 85)
        {
            return QColor(posScaled * 3, 255 - posScaled * 3, 0);
        }
        else if (posScaled < 170)
        {
            posScaled -= 85;
            return QColor(255 - posScaled * 3, 0, posScaled * 3);
        }
        else
        {
            posScaled -= 170;
            return QColor(0, posScaled * 3, 255 - posScaled);
        }
    };

    for (unsigned int j = 0; j < 4; j++)
    {
        double timeOffset = double(this->counter) / 250.0;

        for (unsigned int i = 0; i < NR_LED_LIST[j]; i++)
        {
            unsigned int timeOffsetInArray = (unsigned int)(timeOffset * NR_LED_LIST[j]);
            unsigned int idx = OFFSET_LIST[j] + ((i + timeOffsetInArray) % NR_LED_LIST[j]);
            double pos = double(i) / NR_LED_LIST[j];
            auto c = getColorForPos(pos);
            frame.data[idx] = getColorForPos(pos);
        }
    }

    this->counter++;
    if (this->counter > 250) 
    {
        this->counter = 0;
    }

    return true;
}
