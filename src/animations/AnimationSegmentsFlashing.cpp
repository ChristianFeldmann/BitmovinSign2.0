#include "AnimationSegmentsFlashing.h"

AnimationSegmentsFlashing::AnimationSegmentsFlashing(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    this->animationParameters.push_back(std::make_shared<AnimationParameter>("color", &this->color));
    this->animationParameters.push_back(std::make_shared<AnimationParameter>("timeOffsetBetweenSegments", &this->timeOffsetBetweenSegments));
    this->animationParameters.push_back(std::make_shared<AnimationParameter>("timeToWaitFullColor", &this->timeToWaitFullColor));
}

void AnimationSegmentsFlashing::reset()
{
    this->counter = 0;
}

bool AnimationSegmentsFlashing::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);
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
            QColor c = this->color;
            c.setAlpha(int(intensity * 255));
            frame.setRangeToColor(OFFSET_LIST[i], NR_LED_LIST[i], c);
        }
    }

    this->counter++;
    const unsigned animationDuration = 100 + this->timeToWaitFullColor + 4 * this->timeOffsetBetweenSegments;
    if (this->counter > animationDuration)
    {
        this->counter = 0;
        return true;
    }

    return false;
}
