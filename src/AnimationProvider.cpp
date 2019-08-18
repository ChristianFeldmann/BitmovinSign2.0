#include "AnimationProvider.h"

#include <random>

#include "animations/AnimationConstantColor.h"
#include "animations/AnimationHighlightRotation.h"
#include "animations/AnimationRunningDot.h"
#include "animations/AnimationHighlightSparkling.h"
#include "animations/AnimationRainbow.h"
#include "animations/AnimationSegmentsFlashing.h"
#include "animations/AnimationUllas.h"
#include "animations/AnimationImageBase.h"
#include "animations/AnimationImageFire.h"
#include "animations/AnimationImageColorWipe.h"
#include "animations/AnimationImageCircleWipe.h"

const std::vector<AnimationProvider::IFactory*> AnimationProvider::factoryList({
    new Factory<AnimationConstantColor>,
    new Factory<AnimationHighlightRotation>,
    new Factory<AnimationRunningDot>,
    new Factory<AnimationHighlightSparkling>,
    new Factory<AnimationRainbow>,
    new Factory<AnimationSegmentsFlashing>,
    new Factory<AnimationUllas>,
    new Factory<AnimationImageFire>,
    new Factory<AnimationImageColorWipe>,
    new Factory<AnimationImageCircleWipe>
});

QStringList AnimationProvider::getAnimationList()
{
    QStringList names;
    for (size_t i = 0; i < factoryList.size(); i++)
    {
        auto a = factoryList[i]->create();
        names.append(a->getName());
    }
    return names;
}

AnimationStack AnimationProvider::getAnimationsByName(QStringList names)
{
    AnimationStack newStack;
    for (auto name : names)
    {
        for (size_t i = 0; i < factoryList.size(); i++)
        {
            auto a = factoryList[i]->create();
            if (a->getName() == name)
            {
                newStack.addAnimation(a);
            }
        }
    }
    return newStack;
}

AnimationStack AnimationProvider::getRandomAnimation()
{
    auto nrAnimations = factoryList.size();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned> dist(0, unsigned(nrAnimations) - 1);

    unsigned newAnimationIndex = dist(mt);

    AnimationStack newStack;
    newStack.addAnimation(factoryList[newAnimationIndex]->create());
    return newStack;
}
