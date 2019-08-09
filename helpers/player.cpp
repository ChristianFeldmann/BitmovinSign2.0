#include "player.h"

Player::Player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);
}

void Player::timerEvent(QTimerEvent *event)
{
    Frame frame;
    if (this->animation != nullptr)
        this->animation->render_frame(frame);
    if (this->debugger != nullptr)
        this->debugger->draw(frame);
    if (this->output != nullptr)
        this->output->pushData(frame);
}

void Player::set_animation(animationInterface *animation)
{
    this->animation = animation;
}

void Player::set_output(Output *output)
{
    this->output = output;
}

void Player::set_debugger(debugger_widget *debugger)
{
    this->debugger = debugger;
}

