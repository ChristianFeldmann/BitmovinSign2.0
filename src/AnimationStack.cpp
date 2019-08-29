#include "AnimationStack.h"

#include <QImage>

#include "animations/AnimationConstantColor.h"
#include "animations/AnimationHighlightRotation.h"
#include "animations/AnimationRunningDot.h"
#include "animations/AnimationHighlightSparkling.h"
#include "animations/AnimationRainbow.h"
#include "animations/AnimationSegmentsFlashing.h"
#include "animations/AnimationUllas.h"
#include "animations/AnimationImageFire.h"
#include "animations/AnimationImageColorWipe.h"
#include "animations/AnimationImageCircleWipe.h"

namespace
{
    // For easy creation of ne animations
    struct IFactory { virtual std::shared_ptr<AnimationBase> create(AnimationTreeBase *parent) = 0; };
    template< typename T > struct Factory : public IFactory
    {
        virtual std::shared_ptr<AnimationBase> create(AnimationTreeBase *parent)
        {
            return std::make_shared<T>(parent);
        }
    };

    const std::vector<IFactory*> factoryList({
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
}

AnimationStack::AnimationStack(AnimationTreeBase *rootPlaylist, QStringList animations) :
    AnimationTreeBase(rootPlaylist)
{
    for (QString &animation : animations)
    {
        addAnimationFromString(animation);
    }
}

AnimationTreeBase *AnimationStack::child(int number)
{
    if (number >= 0 && number < this->animations.size())
    {
        return this->animations[number].get();
    }
    return nullptr;
}

size_t AnimationStack::childCount() const
{
    return this->animations.size();
}

int AnimationStack::childNumber(AnimationTreeBase *child) const
{
    for (size_t i = 0; i < this->animations.size(); i++)
    {
        if (this->animations[i].get() == child)
        {
            return int(i);
        }
    }
    return -1;
}

QVariant AnimationStack::data(int column) const
{
    if (column == 0)
    {
        return QVariant("Stack");
    }

    return {};
}

bool AnimationStack::renderStack(Frame &output, RenderMemory &renderMemory)
{
    output.clearFrame();

    for (int i = 0; i < this->animations.size(); i++)
    {
        auto animation = this->animations[i];
        if (renderMemory.imageMap.count(i) == 0)
        {
            renderMemory.imageMap.insert(std::map<int, QImage>::value_type(i, QImage(imageSize, QImage::Format_ARGB32)));
        }
        if (animation->renderFrame(renderMemory.frameMap[i], renderMemory.imageMap[i]))
        {
            this->animationsFinished++;
        }
        output.blendWithFrame(renderMemory.frameMap[i]);
    }

    if (this->animationsFinished > 0 && this->animationsFinished == this->animations.size())
    {
        this->animationsFinished = 0;
        return true;
    }
    return false;
}

void AnimationStack::resetAnimations()
{
    for (auto &animation : this->animations)
    {
        animation->reset();
    }
}

QStringList AnimationStack::getAnimationList()
{
    QStringList names;
    for (size_t i = 0; i < factoryList.size(); i++)
    {
        auto a = factoryList[i]->create(nullptr);
        names.append(a->getName());
    }
    return names;
}

void AnimationStack::addAnimationFromString(QString &name)
{
    auto nameAndParameters = name.split("|");
    QString animationName = nameAndParameters[0];

    for (size_t i = 0; i < factoryList.size(); i++)
    {
        auto a = factoryList[i]->create(this);
        if (a->getName() == animationName)
        {
            for (int i = 1; i < nameAndParameters.size(); i++)
            {
                auto parameterAndValue = nameAndParameters[i].split("=");
                if (parameterAndValue.count() == 2)
                {
                    a->setPropertie(parameterAndValue[0], parameterAndValue[1]);
                }
            }
            this->animations.push_back(a);
        }
    }
}
