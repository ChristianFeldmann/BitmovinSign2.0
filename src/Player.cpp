#include "Player.h"

#include <Constants.h>
#include "animations/AnimationImageBase.h"
#include "AnimationProvider.h"

Player::Player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);
    this->currentAnimation = AnimationProvider::getRandomAnimation();
    //this->currentAnimation = AnimationProvider::getAnimationByName("HighlightSparkling");
    //this->currentAnimation = AnimationProvider::getAnimationsByName({"ConstantColor", "HighlightSparkling" });
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (this->currentAnimation.renderFrame())
    {
        static const int minimumAnimationRuntime = 500;
        if (currentAnimationRuntime > minimumAnimationRuntime)
        {
            currentAnimation = AnimationProvider::getRandomAnimation();
            currentAnimationRuntime = 0;
        }
    }
    currentAnimationRuntime++;

    if (this->debugger != nullptr)
    {
        this->debugger->draw(this->currentAnimation.frame, currentAnimation);
    }
    this->output.pushData(this->currentAnimation.frame);
}

void Player::set_debugger(DebuggerWidget *debugger)
{
    this->debugger = debugger;
}
