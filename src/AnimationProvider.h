#pragma once

#include "AnimationInterface.h"
#include "AnimationStack.h"
#include <QStringList>

class AnimationProvider
{
public:
    AnimationProvider() = default;
    ~AnimationProvider() = default;

    static QStringList getAnimationList();
    static AnimationStack getAnimationsByName(QStringList names);

    static AnimationStack getRandomAnimation();

private:

    struct IFactory { virtual std::shared_ptr<AnimationInterface> create() = 0; };

    template< typename T > struct Factory : public IFactory 
    {
        virtual std::shared_ptr<AnimationInterface> create()
        {
            return std::make_shared<T>();
        }
    };

    static const std::vector<IFactory*> factoryList;
    static const std::vector<QStringList> randomAnimationPool;
};
