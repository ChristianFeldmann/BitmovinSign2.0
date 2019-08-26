#include "AnimationPlaylist.h"

AnimationStack &AnimationPlaylist::getAnimationStack(unsigned idx)
{
    return this->animationStackList[idx];
}

AnimationTreeBase *AnimationPlaylist::child(int number)
{
    return &this->animationStackList.at(number);
}

size_t AnimationPlaylist::childCount() const 
{ 
    return this->animationStackList.size(); 
}

int AnimationPlaylist::childNumber(AnimationTreeBase *child) const
{
    for (size_t i = 0; i < this->animationStackList.size(); i++)
    {
        if (&this->animationStackList[i] == child)
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

void AnimationPlaylist::createPlaylist()
{
    const std::vector<QStringList> playlist({
        {"ConstantColor|color=#0a394b", "HighlightSparkling"},
        {"ConstantColor|color=#0a394b", "HighlightRotation|color=#FFFFFF"},
        {"Fire", "HighlightRotation|color=#FFFFFF"},
        {"ColorWipe|direction=left_to_right"},
    });

    for (QStringList stack : playlist)
    {
        this->animationStackList.push_back(AnimationStack(this, stack));
    }
}
