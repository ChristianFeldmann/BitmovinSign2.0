#include "AnimationSegmentsFlashing.h"

AnimationSegmentsFlashing::AnimationSegmentsFlashing()
{
    color = LedColor::bitmovinBlue;
}

AnimationSegmentsFlashing::AnimationSegmentsFlashing(LedColor &color, unsigned int timeOffsetBetweenSegments, unsigned int timeToWaitFullColor)
{
    this->color = color;
    this->timeOffsetBetweenSegments = timeOffsetBetweenSegments;
    this->timeToWaitFullColor = timeToWaitFullColor;
}

void AnimationSegmentsFlashing::renderFrame(Frame &frame)
{
    const unsigned int ledOffsets[] = OFFSET_LIST;
    const unsigned int ledNrs[] = NR_LED_LIST;

    for (int i = 0; i < 4; i++)
    {
        int partCounter = this->counter - this->timeOffsetBetweenSegments * i;
        if (partCounter > 0 && partCounter < 100 + this->timeToWaitFullColor)
        {
            double intensity = 0;
            if (partCounter < 50)
            {
                intensity = double(partCounter) / 50.0;
            }
            else if (partCounter < 50 + this->timeToWaitFullColor)
            {
                intensity = 1;
            }
            else
            {
                intensity = double(100 + this->timeToWaitFullColor - partCounter) / 50;
            }
            LedColor color = LedColor::interpolateColors(LedColor::black, this->color, intensity);
            frame.setRangeOfLedToColor(ledOffsets[i], ledNrs[i], color);
        }
    }

    this->counter++;
    const unsigned int animationDuration = 100 + this->timeToWaitFullColor + 4 * this->timeOffsetBetweenSegments;
    if (this->counter > animationDuration)
    {
        this->counter = 0;
    }
}
