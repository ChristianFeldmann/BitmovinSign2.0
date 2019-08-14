#include "Player.h"

#include <Constants.h>
#include "animations/AnimationImageBase.h"

Player::Player(AnimationList animationList, QObject *parent):QObject(parent)
, animationList(animationList)
{
    this->timer.start(20, Qt::PreciseTimer, this);
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    Frame frame = Frame(NR_LED_TOTAL);

    if (currentAnimationIndex > animationList.size())
    {
        return;
    }

    if (animationList[currentAnimationIndex]->renderFrame(frame))
    {
        if (currentAnimationRuntime > 500)
        {
            currentAnimationIndex = (currentAnimationIndex + 1) % animationList.size();
            animationList[currentAnimationIndex]->reset();
            currentAnimationRuntime = 0;
        }
    }
    currentAnimationRuntime++;

    if (this->debugger != nullptr)
    {
        auto animationImage = std::dynamic_pointer_cast<AnimationImageBase>(animationList[currentAnimationIndex]);
        this->debugger->draw(frame, animationImage);
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
