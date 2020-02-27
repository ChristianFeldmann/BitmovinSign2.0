#include "AnimationTreeBase.h"

#include <cassert>
#include <QDebug>

bool AnimationTreeBase::canDropItem(QDomElement &root) const
{
    QString tagName = root.tagName().toLower();
    const ItemType itemType = this->getItemType();
    if ((tagName == "stack" && itemType == Playlist) || (tagName != "stack" && itemType == Stack))
    {
        return true;
    }
    return false;
}
