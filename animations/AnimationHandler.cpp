#include "AnimationHandler.h"

// Include all used animations here:
#include "animationConstantColor.h"
#include "animationRunningDot.h"

std::unique_ptr<AnimationInterface> AnimationHandler::getNextAnimation()
{
    std::unique_ptr<AnimationInterface> animation(new AnimationConstantColor());
    return animation;
}
