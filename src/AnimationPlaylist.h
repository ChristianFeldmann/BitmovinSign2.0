#pragma once

#include <memory>

#include "AnimationStack.h"
#include "AnimationTreeBase.h"

/* The AnimationPlaylist is the root of our playlist
 */
class AnimationPlaylist : public AnimationTreeBase
{
public:
    AnimationPlaylist() : AnimationTreeBase(nullptr) {};
    ~AnimationPlaylist() = default;

    // Overrides from the AnimationTreeBase
    AnimationTreeBase *child(int number) override;
    size_t childCount() const override;
    int childNumber(AnimationTreeBase *child) const override;
    QVariant data(int column) const override;

private:
    // We will replace this by some sort of loading / saving to file
    void createPlaylist();

    std::vector<AnimationStack> animationStackList;
};
