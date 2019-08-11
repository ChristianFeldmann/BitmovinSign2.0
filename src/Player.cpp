#include <Player.h>

Player::Player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);

    animationHandler.createNextAnimationStack(animationStack);
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
