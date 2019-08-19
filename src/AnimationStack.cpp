#include "AnimationStack.h"

#include <QDebug>

void AnimationStack::setPropertie(QString propertyName, QString value)
{
    qDebug() << "Unable to set property '" << propertyName << "' to value '" << value << "'. You can not set properties on an animation stack.";
}

bool AnimationStack::renderFrame()
{
    this->frame.clearFrame();

    for (auto animation : this->animations)
    {
        if (animation->renderFrame())
        {
            this->animationsFinished++;
        }
        this->frame.blendWithFrame(animation->frame);
    }

    if (this->animationsFinished > 0 && this->animationsFinished == this->animations.size())
    {
        this->animationsFinished = 0;
        return true;
    }
    return false;
}

void AnimationStack::addAnimation(std::shared_ptr<AnimationInterface> animation)
{
    this->animations.push_back(animation);
}
