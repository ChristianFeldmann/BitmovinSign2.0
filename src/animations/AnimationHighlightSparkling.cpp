#include "AnimationHighlightSparkling.h"

#include <random>

AnimationHighlightSparkling::AnimationHighlightSparkling(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("color", &this->sparkColor);
    this->addParameter("speed", &this->sparkSpeed);
    this->addParameter("rate", &this->sparkRate);
}

void AnimationHighlightSparkling::reset()
{
    this->sparks.clear();
    this->sparkCreationCounter = 0.0;
}

void AnimationHighlightSparkling::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);

    const unsigned int offset = 2;

    frame.clearFrame();

    const float timeBetweenSparks = 1 / sparkRate;
    if (this->sparkCreationCounter > timeBetweenSparks)
    {
        // Add a new spark
        Spark s;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dist(0, NR_LED_TOTAL - 1);

        s.position = dist(mt);
        this->sparks.push_back(s);
        this->sparkCreationCounter = 0.0;
    }
    this->sparkCreationCounter += float(0.02);

    // Render sparks
    for (auto it = this->sparks.begin(); it != this->sparks.end(); it++)
    {
        double sparkleIntensity = ((*it).counter < 50) ? ((*it).counter / 50.0) : ((100.0 - (*it).counter) / 50);

        static const double offsetRatios[] = { 0.25, 0.5, 1.0, 0.5, 0.25 };
        for (int i = -2; i < 3; i++)
        {
            double ratio = sparkleIntensity * offsetRatios[i + 2];
            unsigned int idx = this->getRelativeIndexWrap((*it).position, i);

            auto setAlpha = frame.data[idx].alpha();
            frame.data[idx] = this->sparkColor;
            if (setAlpha == 0)
            {
                frame.data[idx].setAlpha(int(ratio * 255));
            }
            else
            {
                auto newAlpha = clip<int>(setAlpha + int(ratio * 255), 0, 255);
                frame.data[idx].setAlpha(newAlpha);
            }
        }
        (*it).counter += this->sparkSpeed;
    }

    this->sparks.erase(std::remove_if(this->sparks.begin(),
                                     this->sparks.end(),
                                     [](Spark s) {return s.counter >=100;}),
                       this->sparks.end());
}

unsigned AnimationHighlightSparkling::getRelativeIndexWrap(unsigned int idx, int offset)
{
    int newIndex = idx + offset;
    if (idx < NR_LED_BACKGROUND)
    {
        // Background
        if (newIndex < 0)
            return NR_LED_BACKGROUND + newIndex;
        if (newIndex >= int(NR_LED_BACKGROUND))
            return newIndex - NR_LED_BACKGROUND;
    }
    else if (idx < OFFSET_PART_MIDDLE)
    {
        // Part left
        if (newIndex < int(OFFSET_PART_LEFT))
            return newIndex + NR_LED_PART_LEFT;
        if (newIndex >= int(OFFSET_PART_MIDDLE))
            return newIndex - NR_LED_PART_LEFT;

    }
    else if (idx < OFFSET_PART_RIGHT)
    {
        // Part middle
        if (newIndex < int(OFFSET_PART_MIDDLE))
            return newIndex + NR_LED_PART_MIDDLE;
        if (newIndex >= int(OFFSET_PART_RIGHT))
            return newIndex - NR_LED_PART_MIDDLE;
    }
    else
    {
        // Part right
        if (newIndex < int(OFFSET_PART_RIGHT))
            return newIndex + NR_LED_PART_RIGHT;
        if (newIndex >= int(NR_LED_TOTAL))
            return newIndex - NR_LED_PART_RIGHT;
    }
    return newIndex;
}
