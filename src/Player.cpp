#include "Player.h"

#include "animations/AnimationImageBase.h"
#include "AnimationProvider.h"
#include "Constants.h"

#include <QDebug>

Player::Player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);
    this->currentAnimation = AnimationProvider::getAnimationsByName({"ConstantColor|color=#0a394b", "HighlightSparkling"});
    
    connect(&this->fpsTimer, &QTimer::timeout, this, &Player::fpsTimerTimeout);
    this->fpsTimer.start(1000);
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

    emit this->updateDebugger(this->currentAnimation);
    this->output.pushData(this->currentAnimation.frame);
    
    this->fpsDrawCounter++;
}

void Player::fpsTimerTimeout()
{
    qDebug() << "FPS: " << this->fpsDrawCounter;
    emit this->updateFPS(this->fpsDrawCounter);
    this->fpsDrawCounter = 0;
}
