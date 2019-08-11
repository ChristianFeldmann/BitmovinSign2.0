#include "Player.h"

Player::Player(QObject *parent):QObject(parent)
{
    this->frameTimer.start(20, Qt::PreciseTimer, this);
    this->animationChangeTimer.start(5000);

    animationHandler.createNextAnimationStack(animationStack);
    this->connect(&this->animationChangeTimer, &QTimer::timeout, this, &Player::changeAnimationTimer);
}

void Player::changeAnimationTimer()
{
    this->animationIndex++;
    if (this->animationIndex >= 5)
    {
        this->animationIndex = 0;
    }
    animationHandler.createNextAnimationStack(animationStack, this->animationIndex);
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    Frame frame;
    for (auto &animation : this->animationStack)
    {
        animation->renderFrame(frame);
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

