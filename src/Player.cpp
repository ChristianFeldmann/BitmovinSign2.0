#include "Player.h"

#include "Constants.h"

#include <QDebug>

Player::Player(QObject *parent):QObject(parent)
{
    this->timer.start(20, Qt::PreciseTimer, this);
    this->currentAnimationStackIndex = 0;
    
    connect(&this->fpsTimer, &QTimer::timeout, this, &Player::fpsTimerTimeout);
    this->fpsTimer.start(1000);

    playlist.createDefaultPlaylist();
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    auto animationStack = this->playlist.getAnimationStack(this->currentAnimationStackIndex);
    if (animationStack == nullptr)
    {
        return;
    }

    QStringList animationNames = animationStack->getAnimationList();
    if (animationStack->renderStack(this->outputFrame, this->renderMemory))
    {
        static const int minimumAnimationRuntime = 500;
        if (currentAnimationRuntime > minimumAnimationRuntime)
        {
            this->currentAnimationStackIndex++;
            if (this->currentAnimationStackIndex > this->playlist.childCount())
            {
                this->currentAnimationStackIndex = 0;
            }
            currentAnimationRuntime = 0;
        }
    }
    currentAnimationRuntime++;

    emit this->updateDebugger(animationNames, &this->outputFrame, &this->renderMemory);
    this->output.pushData(this->outputFrame);
    
    this->fpsDrawCounter++;
}

void Player::fpsTimerTimeout()
{
    qDebug() << "FPS: " << this->fpsDrawCounter;
    emit this->updateFPS(this->fpsDrawCounter);
    this->fpsDrawCounter = 0;
}
