#include "AnimationStack.h"

#include <QImage>

#include "animations/AnimationAlarm.h"
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
        new Factory< AnimationAlarm>,
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

AnimationStack::AnimationStack(AnimationTreeBase *rootPlaylist) :
    AnimationTreeBase(rootPlaylist)
{
}

AnimationStack::AnimationStack(AnimationTreeBase *rootPlaylist, QDomElement &root) :
    AnimationTreeBase(rootPlaylist)
{
    if (root.tagName() != "stack")
    {
        return;
    }

    QDomNodeList children = root.childNodes();
    for (int i = 0; i < children.length(); i++)
    {
        // Parse the child items
        QDomElement childElem = children.item(i).toElement();
        this->addAnimationFromDomElement(childElem);
    }
}

AnimationTreeBase *AnimationStack::child(int number) const
{
    if (number >= 0 && number < int(this->animations.size()))
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

bool AnimationStack::removeChildren(int pos, int count)
{
    if (pos < 0 || pos > int(this->animations.size()))
    {
        return false;
    }

    this->animations.erase(this->animations.begin() + pos, this->animations.begin() + pos + count);
    return true;
}

bool AnimationStack::insertAnimation(int pos, QString type)
{
    if (pos < 0 || pos > int(this->animations.size()))
        return false;

    auto newAnimation = this->createNewAnimation(type);
    if (pos == -1)
    {
        this->animations.push_back(newAnimation);
    }
    else
    {
        this->animations.insert(this->animations.begin() + pos, newAnimation);
    }
    
    return true;
}

bool AnimationStack::renderStack(Frame &output, RenderMemory &renderMemory)
{
    output.clearFrame();

    for (unsigned i = 0; i < unsigned(this->animations.size()); i++)
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
        renderMemory.imageUsed[i] = animation->usesImage();
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

QStringList AnimationStack::getChildAnimationNames()
{
    QStringList names;
    for (auto animation : this->animations)
    {
        names.push_back(animation->getName());
    }
    return names;
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

std::shared_ptr<AnimationBase> AnimationStack::createNewAnimation(QString animationName)
{
    for (size_t i = 0; i < factoryList.size(); i++)
    {
        auto a = factoryList[i]->create(this);
        if (a->getName() == animationName)
        {
            return a;
        }
    }
    return {};
}

bool AnimationStack::savePlaylist(QDomElement &root) const
{
    QDomElement d = root.ownerDocument().createElement("stack");
    bool success = true;
    for (auto animation : this->animations)
    {
        success &= animation->savePlaylist(d);
    }
    root.appendChild(d);
    return success;
}

void AnimationStack::addAnimationFromDomElement(QDomElement &elem, int position)
{
    QString animationName = elem.tagName();
    auto newAnimation = this->createNewAnimation(animationName);
    if (newAnimation)
    {
        newAnimation->loadProperties(elem);
    }
    if (position >= 0)
    {
        auto it = this->animations.begin();
        this->animations.insert(it + position, newAnimation);
    }
    else
    {
        this->animations.push_back(newAnimation);
    }
}