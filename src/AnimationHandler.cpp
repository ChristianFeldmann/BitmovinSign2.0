#include "AnimationHandler.h"

// Include all used animations here:
#include "animations/AnimationConstantColor.h"
#include "animations/AnimationHighlightRotation.h"
#include "animations/AnimationRunningDot.h"

void AnimationHandler::createNextAnimationStack(std::vector<std::unique_ptr<AnimationInterface>> &animationList)
{
    animationList.clear();
    animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationConstantColor()));
    animationList.push_back(std::unique_ptr<AnimationInterface>(new AnimationHighlightRotation()));
}
