#include "AnimationHighlightRotation.h"

#include<assert.h>
#include <QDebug>

AnimationHighlightRotation::AnimationHighlightRotation()
{
    color = BITMOVIN_BLUE;
}

void AnimationHighlightRotation::setPropertie(QString propertyName, QString value)
{
    if (propertyName.toLower() == "color")
    {
        this->color = QColor(value);
    }
    else
    {
        qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. Unknown option for class " << typeid(*this).name();
    }
}

void AnimationHighlightRotation::reset()
{
    rotationCounters[0] = 0;
    rotationCounters[1] = 0;
    rotationCounters[2] = 0;
    rotationCounters[3] = 0;
}

bool AnimationHighlightRotation::renderFrame()
{
    auto setLeds = [&](unsigned int ledStartOffset, unsigned int nrLed, unsigned int shift, const unsigned int lengths[], int lengthsSize)
    {
        unsigned int idx = shift;
        for (int i = 0; i < lengthsSize; i++)
        {
            for (unsigned int j = 0; j < lengths[i]; j++)
            {
                if (i % 2 == 0)
                {
                    assert(ledStartOffset + idx < NR_LED_TOTAL);
                    this->frame.data[ledStartOffset + idx] = this->color;
                }
                else
                {
                    this->frame.data[ledStartOffset + idx] = Qt::transparent;
                }
                idx++;
                idx = idx % nrLed;
            }
        }
    };

    // Background
    static const unsigned int lengthsBackground[] = {11, 10, 10, 10, 11, 10, 10, 11, 10, 10, 11, 10, 10, 11, 10, 10, 10, 11, 10, 10};
    setLeds(0, NR_LED_BACKGROUND, this->rotationCounters[0], lengthsBackground, 20);

    // Part left
    static const unsigned int lengthsLeft[] = {11, 12, 11, 12};
    setLeds(OFFSET_PART_LEFT, NR_LED_PART_LEFT, this->rotationCounters[1], lengthsLeft, 4);

    // Middle
    static const unsigned int lengthsMiddle[] = {11, 12, 11, 11, 11, 12, 11, 11};
    setLeds(OFFSET_PART_MIDDLE, NR_LED_PART_MIDDLE, this->rotationCounters[2], lengthsMiddle, 8);

    // Right
    static const unsigned int lengthsRight[] = {10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11};
    setLeds(OFFSET_PART_RIGHT, NR_LED_PART_RIGHT, this->rotationCounters[3], lengthsRight, 14);

    if (++this->rotationCounters[0] >= NR_LED_BACKGROUND)
    {
        this->rotationCounters[0] = 0;
    }
    if (++this->rotationCounters[1] >= NR_LED_PART_LEFT)
    {
        this->rotationCounters[1] = 0;
    }
    if (++this->rotationCounters[2] >= NR_LED_PART_MIDDLE)
    {
        this->rotationCounters[2] = 0;
    }
    if (++this->rotationCounters[3] >= NR_LED_PART_RIGHT)
    {
        this->rotationCounters[3] = 0;
    }

    return true;
}
