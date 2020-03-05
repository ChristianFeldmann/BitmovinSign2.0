#pragma once

#include <QDomElement>
#include <QList>
#include <QPointer>

#include "animation/Parameter.h"
#include "animation/AnimationTreeBase.h"

class GeneralSettings : public AnimationTreeBase
{
public:
    GeneralSettings(AnimationTreeBase *rootPlaylist);
    ~GeneralSettings() = default;

    // Overload from AnimationTreeBase
    virtual AnimationTreeBase *child(int number) const override { Q_UNUSED(number); return nullptr; }
    virtual size_t childCount() const override { return 0; }
    virtual int childNumber(AnimationTreeBase *child) const override { Q_UNUSED(child); return -1; }
    virtual QVariant data(int column) const override;
    bool removeChildren(int pos, int rows) override { Q_UNUSED(pos); Q_UNUSED(rows); return false; }
    
    bool savePlaylist(QDomElement &root) const override;
    bool loadProperties(QDomElement &root);

    int getAnimationTransitionTime() const { return this->animationTransitionTime; }

private:
    int animationTransitionTime {10};

    virtual ItemType getItemType() const { return ItemType::GeneralSettings; }
};
