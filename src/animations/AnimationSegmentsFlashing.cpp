#include "AnimationSegmentsFlashing.h"

AnimationSegmentsFlashing::AnimationSegmentsFlashing()
{
    color = BITMOVIN_BLUE;
}

AnimationSegmentsFlashing::AnimationSegmentsFlashing(const QColor &color, unsigned int timeOffsetBetweenSegments, unsigned int timeToWaitFullColor)
{
    this->color = color;
    this->timeOffsetBetweenSegments = timeOffsetBetweenSegments;
    this->timeToWaitFullColor = timeToWaitFullColor;
}

bool AnimationSegmentsFlashing::renderFrame(Frame &frame)
{
    frame = getBlackFrame();

    for (int i = 0; i < 4; i++)
    {
        unsigned partCounter = this->counter - this->timeOffsetBetweenSegments * i;
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
            QColor color = interpolateColors(Qt::black, this->color, intensity);
            setRangeOfLedToColor(frame, OFFSET_LIST[i], NR_LED_LIST[i], color);
        }
    }

    this->counter++;
    const unsigned int animationDuration = 100 + this->timeToWaitFullColor + 4 * this->timeOffsetBetweenSegments;
    if (this->counter > animationDuration)
    {
        this->counter = 0;
        return false;
    }

    return true;
}
