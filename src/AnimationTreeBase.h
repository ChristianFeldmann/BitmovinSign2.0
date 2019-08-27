#pragma once

#include <memory>
#include <QVariant>

/* This base adds the ability for a hierarchical structure where
 * each item in the tree knows his parents and can have children.
 *
 * This is mostly useful for the QAbstractTreeModel which we use to
 * represent and edit the playlist.
 */
class AnimationTreeBase
{
public:
    AnimationTreeBase() = delete;
    AnimationTreeBase(AnimationTreeBase *parent) { this->parent = parent; }
    ~AnimationTreeBase() = default;

    virtual AnimationTreeBase *child(int number) = 0;
    virtual size_t childCount() const = 0;
    virtual int childNumber(AnimationTreeBase *child) const = 0;
    virtual QVariant data(int column) const = 0;

    AnimationTreeBase *getParent() { return this->parent; }

protected:
    AnimationTreeBase *parent{ nullptr };
};