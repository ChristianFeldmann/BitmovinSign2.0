#include "AnimationPlaylist.h"

std::shared_ptr<AnimationStack> AnimationPlaylist::getAnimationStack(unsigned idx) const
{
    if (idx < 0 || idx >= this->animationStackList.size())
    {
        return nullptr;
    }
    return this->animationStackList[idx];
}

int AnimationPlaylist::getAnimationStackIndex(AnimationTreeBase *stack) const
{
    for (size_t i = 0; i < this->animationStackList.size(); i++)
    {
        if (this->animationStackList[i].get() == stack)
        {
            return int(i);
        }
    }
    return -1;
}

AnimationTreeBase *AnimationPlaylist::child(int number)
{
    return this->animationStackList.at(number).get();
}

size_t AnimationPlaylist::childCount() const 
{ 
    return this->animationStackList.size(); 
}

int AnimationPlaylist::childNumber(AnimationTreeBase *child) const
{
    for (size_t i = 0; i < this->animationStackList.size(); i++)
    {
        if (this->animationStackList[i].get() == child)
        {
            return int(i);
        }
    }
    return 0;
}

QVariant AnimationPlaylist::data(int column) const
{
    Q_UNUSED(column);
    return {};
}

void AnimationPlaylist::createDefaultPlaylist()
{
    const std::vector<QStringList> playlist({
        {"ConstantColor|color=#0a394b", "HighlightSparkling"},
        {"ConstantColor|color=#0a394b", "HighlightRotation|color=#FFFFFF"},
        {"Fire", "HighlightRotation|color=#FFFFFF"},
        {"ColorWipe|direction=left_to_right"},
    });

    for (QStringList stack : playlist)
    {
        auto newStack = std::make_shared<AnimationStack>(this, stack);
        this->animationStackList.push_back(newStack);
    }
}
