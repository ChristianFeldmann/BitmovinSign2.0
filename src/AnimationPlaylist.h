#pragma once

#include <memory>

#include "AnimationStack.h"
#include "AnimationTreeBase.h"

/* The AnimationPlaylist is the root of our tree
 */
class AnimationPlaylist : public AnimationTreeBase
{
public:
    AnimationPlaylist() : AnimationTreeBase(nullptr) {};
    ~AnimationPlaylist() = default;

    std::shared_ptr<AnimationStack> getAnimationStack(unsigned idx) const;
    int getAnimationStackIndex(AnimationTreeBase *stack) const;

    // Overrides from the AnimationTreeBase
    AnimationTreeBase *child(int number) override;
    size_t childCount() const override;
    int childNumber(AnimationTreeBase *child) const override;
    QVariant data(int column) const override;

    // We will replace this by some sort of loading / saving to file
    void createDefaultPlaylist();

private:
    std::vector<std::shared_ptr<AnimationStack>> animationStackList;
};
