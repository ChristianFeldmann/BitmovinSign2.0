#pragma once

#include <memory>

#include "AnimationStack.h"
#include "AnimationTreeBase.h"

#include <QDomElement>

/* The AnimationPlaylist is the root of our tree
 */
class AnimationPlaylist : public AnimationTreeBase
{
public:
    AnimationPlaylist() : AnimationTreeBase(nullptr) {};
    ~AnimationPlaylist() = default;

    bool loadPlaylistFile(QString filename);
    QString getPlaylistString() const;
    bool createDefaultPlaylist();

    std::shared_ptr<AnimationStack> getAnimationStack(unsigned idx) const;
    int getAnimationStackIndex(AnimationTreeBase *stack) const;

    bool insertStack(int position);

    // Overrides from the AnimationTreeBase
    AnimationTreeBase *child(int number) const override;
    size_t childCount() const override;
    int childNumber(AnimationTreeBase *child) const override;
    QVariant data(int column) const override;

    virtual bool removeChildren(int pos, int rows) override;

    bool savePlaylist(QDomElement &root) const override;
    void addStackFromDomElement(QDomElement &elem, int position = -1);

private:
    bool loadPlaylistFromByteArray(QByteArray byteArray);

    std::vector<std::shared_ptr<AnimationStack>> animationStackList;

    virtual ItemType getItemType() const { return Playlist; }
};
