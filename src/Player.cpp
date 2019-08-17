#include "Player.h"

#include <Constants.h>
#include "animations/AnimationImageBase.h"
#include "AnimationProvider.h"

Player::Player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);
    currentAnimation = AnimationProvider::getRandomAnimation();
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    Frame frame = Frame(NR_LED_TOTAL);

    if (currentAnimation.renderFrame(frame))
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
        this->debugger->draw(frame, currentAnimation);
    }
    this->output.pushData(frame);
}

void Player::set_debugger(DebuggerWidget *debugger)
{
    this->debugger = debugger;
}
