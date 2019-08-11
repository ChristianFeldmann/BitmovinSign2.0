#include "AnimationHandler.h"

// Include all used animations here:
#include "AnimationConstantColor.h"
#include "AnimationHighlightRotation.h"
#include "AnimationHighlightSparkling.h"
#include "AnimationRunningDot.h"
#include "AnimationUllas.h"
#include "AnimationSegmentsFlashing.h"
#include "AnimationRainbow.h"

void AnimationHandler::createNextAnimationStack(std::vector<std::unique_ptr<AnimationInterface>> &animationList, unsigned int animationIndex)
{
    animationList.clear();
    if (animationIndex == 0)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationConstantColor()));
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationHighlightRotation()));
    }
    else if (animationIndex == 1)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationConstantColor()));
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationHighlightSparkling()));
    }
    else if (animationIndex == 2)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationSegmentsFlashing(LedColor::bitmovinBlue, 20, 40)));
    }
    else if (animationIndex == 3)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationRainbow()));
    }
    else if (animationIndex == 4)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationUllas()));
    }
}
