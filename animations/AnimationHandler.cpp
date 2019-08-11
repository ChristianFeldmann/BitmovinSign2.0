#include "AnimationHandler.h"

// Include all used animations here:
#include "AnimationConstantColor.h"
#include "AnimationHighlightRotation.h"
#include "AnimationRunningDot.h"
#include "AnimationUllas.h"

void AnimationHandler::createNextAnimationStack(std::vector<std::unique_ptr<AnimationInterface>> &animationList)
{
    animationList.clear();
    if (false)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationConstantColor()));
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationHighlightRotation()));
    }
    if (true)
    {
        animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationUllas()));
    }
}
