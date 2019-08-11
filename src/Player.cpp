#include "Player.h"

#include <Constants.h>

Player::Player(AnimationList animationList, QObject *parent):QObject(parent)
, animationList(animationList)
{
    this->timer.start(20, Qt::PreciseTimer, this);
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    Frame frame;

    if (currentAnimation > animationList.size())
    {
        return;
    }

    if (!animationList[currentAnimation]->renderFrame(frame))
    {
        currentAnimation = (currentAnimation + 1) % animationList.size(); 
    }

    if (this->debugger != nullptr)
    {
        this->debugger->draw(frame);
    }
    if (this->output != nullptr)
    {
        this->output->pushData(frame);
    }
}

void Player::set_output(Output *output)
{
    this->output = output;
}

void Player::set_debugger(DebuggerWidget *debugger)
{
    this->debugger = debugger;
}
