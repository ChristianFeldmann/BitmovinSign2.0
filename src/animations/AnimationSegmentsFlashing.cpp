#include "AnimationSegmentsFlashing.h"

AnimationSegmentsFlashing::AnimationSegmentsFlashing(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->addParameter("speed", &this->speed);
    this->addParameter("color", &this->color);
    this->addParameter("timeOffsetBetweenSegments", &this->timeOffsetBetweenSegments);
    this->addParameter("timeToWaitFullColor", &this->timeToWaitFullColor);
}

void AnimationSegmentsFlashing::reset()
{
    this->counter = 0;
}

bool AnimationSegmentsFlashing::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);
    frame.clearFrame();
    for (int i = 0; i < 4; i++)
    {
        float partCounter = this->counter - this->timeOffsetBetweenSegments * i;
        if (partCounter > 0 && partCounter < 100 + this->timeToWaitFullColor)
        {
            float intensity = 0;
            if (partCounter < 50)
            {
                intensity = partCounter / 50.0;
            }
            else if (partCounter < 50 + this->timeToWaitFullColor)
            {
                intensity = 1.0;
            }
            else
            {
                intensity = (100.0 + float(this->timeToWaitFullColor) - partCounter) / 50;
            }
            QColor c = this->color;
            c.setAlpha(int(intensity * 255));
            frame.setRangeToColor(OFFSET_LIST[i], NR_LED_LIST[i], c);
        }
    }

    this->counter += this->speed;
    const unsigned animationDuration = 100 + this->timeToWaitFullColor + 4 * this->timeOffsetBetweenSegments;
    if (this->counter > animationDuration)
    {
        this->counter = 0.0;
        return true;
    }

    return false;
}
