#pragma once

#include "AnimationBase.h"
#include "AnimationTreeBase.h"
#include "RenderMemory.h"

#include <QDomElement>

/* A stack of multiple animations. Rendering the stack will render all animations
 * in the order they were added.
 */
class AnimationStack : public AnimationTreeBase
{
public:
    AnimationStack(AnimationTreeBase *rootPlaylist);
    AnimationStack(AnimationTreeBase *rootPlaylist, QDomElement &root);
    ~AnimationStack() = default;

    bool renderStack(RenderMemory &renderMemory);
    void resetAnimations();

    // Overload from AnimationTreeBase
    virtual AnimationTreeBase *child(int number) const override;
    virtual size_t childCount() const override;
    virtual int childNumber(AnimationTreeBase *child) const override;
    virtual QVariant data(int column) const override;

    bool removeChildren(int pos, int rows) override;
    bool insertAnimation(int position, QString type);

    QStringList getChildAnimationNames();
    
    // Get a list with all names of all known animations
    static QStringList getAnimationList();

    bool savePlaylist(QDomElement &root) const override;
    void addAnimationFromDomElement(QDomElement &elem, int position = -1);

private:
    std::shared_ptr<AnimationBase> createNewAnimation(QString animationName);

    std::vector<std::shared_ptr<AnimationBase>> animations;

    unsigned animationsFinished{ 0 };

    virtual ItemType getItemType() const { return Stack; }

    bool asyncRenderAnimation(unsigned i, RenderMemory &renderMemory);
};
