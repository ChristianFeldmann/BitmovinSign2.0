#include "AnimationHandler.h"

// Include all used animations here:
#include "AnimationConstantColor.h"
#include "AnimationHighlightRotation.h"
#include "AnimationHighlightSparkling.h"
#include "AnimationRunningDot.h"
#include "AnimationUllas.h"
#include "AnimationSegmentsFlashing.h"
#include "AnimationRainbow.h"

void AnimationHandler::createNextAnimationStack(std::vector<std::unique_ptr<AnimationInterface>> &animationList)
{
    animationList.clear();
    if (false)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationConstantColor()));
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationHighlightRotation()));
    }
    if (false)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationConstantColor()));
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationHighlightSparkling()));
    }
    if (false)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationSegmentsFlashing(LedColor::bitmovinBlue, 20, 40)));
    }
    if (true)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationRainbow()));
    }
    if (false)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationUllas()));
    }
}
