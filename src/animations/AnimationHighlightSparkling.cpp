#include "AnimationHighlightSparkling.h"

#include <random>

AnimationHighlightSparkling::AnimationHighlightSparkling()
{
    sparkColor = Qt::white;
}

AnimationHighlightSparkling::AnimationHighlightSparkling(QColor &color)
{
    this->sparkColor = color;
}

void AnimationHighlightSparkling::reset()
{
    this->sparks.clear();
    this->offsetCounter = 0;
}

bool AnimationHighlightSparkling::renderFrame()
{
    const unsigned int duration = 50;
    const unsigned int offset = 2;

    this->frame.clearFrame();

    if (this->offsetCounter > offset)
    {
        // Add a new spark
        Spark s;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dist(0, NR_LED_TOTAL - 1);

        s.position = dist(mt);
        this->sparks.push_back(s);
        this->offsetCounter = 0;
    }
    this->offsetCounter++;

    // Render sparks
    for (auto it = this->sparks.begin(); it != this->sparks.end(); it++)
    {
        double sparkleIntensity = ((*it).counter < 50) ? (double((*it).counter) / 50.0) : (double(100 - (*it).counter) / 50);

        static const double offsetRatios[] = { 0.25, 0.5, 1.0, 0.5, 0.25 };
        for (int i = -2; i < 3; i++)
        {
            double ratio = sparkleIntensity * offsetRatios[i + 2];
            unsigned int idx = this->getRelativeIndexWrap((*it).position, i);
            this->frame.data[idx] = this->sparkColor;
            this->frame.data[idx].setAlpha(int(ratio * 255));
        }
        (*it).counter++;
    }

    this->sparks.erase(std::remove_if(this->sparks.begin(),
                                     this->sparks.end(),
                                     [](Spark s) {return s.counter >=100;}),
                       this->sparks.end());

    return true;
}

unsigned AnimationHighlightSparkling::getRelativeIndexWrap(unsigned int idx, int offset)
{
    int newIndex = idx + offset;
    if (idx < NR_LED_BACKGROUND)
    {
        // Background
        if (newIndex < 0)
            return NR_LED_BACKGROUND + newIndex;
        if (newIndex >= NR_LED_BACKGROUND)
            return newIndex - NR_LED_BACKGROUND;
    }
    else if (idx < OFFSET_PART_MIDDLE)
    {
        // Part left
        if (newIndex < OFFSET_PART_LEFT)
            return newIndex + NR_LED_PART_LEFT;
        if (newIndex >= OFFSET_PART_MIDDLE)
            return newIndex - NR_LED_PART_LEFT;

    }
    else if (idx < OFFSET_PART_RIGHT)
    {
        // Part middle
        if (newIndex < OFFSET_PART_MIDDLE)
            return newIndex + NR_LED_PART_MIDDLE;
        if (newIndex >= OFFSET_PART_RIGHT)
            return newIndex - NR_LED_PART_MIDDLE;
    }
    else
    {
        // Part right
        if (newIndex < OFFSET_PART_RIGHT)
            return newIndex + NR_LED_PART_RIGHT;
        if (newIndex >= NR_LED_TOTAL)
            return newIndex - NR_LED_PART_RIGHT;
    }
    return newIndex;
}