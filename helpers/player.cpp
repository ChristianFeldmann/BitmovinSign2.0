#include "player.h"

player::player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);
}

void player::timerEvent(QTimerEvent *event)
{
    Frame frame;
    if (this->animation != nullptr)
        this->animation->render_frame(frame);
    if (this->debugger != nullptr)
        this->debugger->draw(frame);
}

void player::set_animation(animationInterface *animation)
{
    this->animation = animation;
}

void player::set_debugger(debugger_widget *debugger)
{
    this->debugger = debugger;
}

