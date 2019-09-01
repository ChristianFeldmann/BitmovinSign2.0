#pragma once

#include "AnimationBase.h"
#include "AnimationTreeBase.h"

/* A stack of multiple animations. Rendering the stack will render all animations
 * in the order they were added.
 */
class AnimationStack : public AnimationTreeBase
{
public:
    AnimationStack(AnimationTreeBase *rootPlaylist, QStringList animations = {});
    ~AnimationStack() = default;

    bool renderStack(Frame &output, RenderMemory &renderMemory);
    void resetAnimations();

    // Overload from AnimationTreeBase
    virtual AnimationTreeBase *child(int number) override;
    virtual size_t childCount() const override;
    virtual int childNumber(AnimationTreeBase *child) const override;
    virtual QVariant data(int column) const override;

    bool removeChildren(int pos, int rows) override;
    bool insertAnimation(int position, QString type);

    QStringList getChildAnimationNames();
    
    // Get a list with all names of all known animations
    static QStringList getAnimationList();

private:
    void addAnimationFromString(QString &name, int position=-1);
    std::vector<std::shared_ptr<AnimationBase>> animations;

    unsigned animationsFinished{ 0 };
};
