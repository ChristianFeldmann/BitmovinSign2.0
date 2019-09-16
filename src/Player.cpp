#include "Player.h"

#include "Constants.h"

#include <QDebug>
#include <QDomDocument>

Player::Player(QObject *parent) : QObject(parent)
{
    this->currentAnimationStackIndex = 0;
    
    connect(&this->fpsTimer, &QTimer::timeout, this, &Player::fpsTimerTimeout);
    this->fpsTimer.start(1000);

    this->play();
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    auto animationStack = this->model.getAnimationStack(this->currentAnimationStackIndex);
    if (animationStack == nullptr)
    {
        return;
    }

    const auto renderIndex = this->currentRenderIndex;

    this->waitForLastRender();
    
    // Switch to the next animation?
    static const int minimumAnimationRuntime = 500;
    if (autoSwitchStacks && currentAnimationRuntime > minimumAnimationRuntime)
    {
        this->currentAnimationStackIndex++;
        if (this->currentAnimationStackIndex >= unsigned(this->model.rowCount()))
        {
            this->currentAnimationStackIndex = 0;
        }
        currentAnimationRuntime = 0;
        this->model.getAnimationStack(this->currentAnimationStackIndex)->resetAnimations();
    }
    currentAnimationRuntime++;

    this->startNextRender();

    QStringList animationNames = animationStack->getChildAnimationNames();
    emit this->updateDebugger(animationNames, &this->renderMemory[renderIndex]);
    this->output.pushData(this->renderMemory[renderIndex].outputFrame);
    
    this->fpsDrawCounter++;
}

void Player::fpsTimerTimeout()
{
    qDebug() << "FPS: " << this->fpsDrawCounter;
    emit this->updateFPS(this->fpsDrawCounter);
    this->fpsDrawCounter = 0;
}

void Player::setCurrentAnimation(AnimationTreeBase *item)
{
    int index = this->model.getAnimationStackIndex(item);
    if (index >= 0)
    {
        this->currentAnimationStackIndex = index;
        currentAnimationRuntime = 0;
        this->model.getAnimationStack(this->currentAnimationStackIndex)->resetAnimations();
        autoSwitchStacks = false;
    }
}

void Player::pause()
{
    this->timer.stop();
    this->playing = false;
}

void Player::play()
{
    int millisecond = 1000 / this->targetFPS;
    this->timer.start(millisecond, Qt::PreciseTimer, this);
    this->playing = true;
}

void Player::step()
{
    this->timerEvent(nullptr);
}

bool Player::loadPlaylistFile(QString filename)
{
    return this->model.loadPlaylistFile(filename);
}

void Player::setTargetFPS(int value)
{
    this->targetFPS = value;
    if (this->playing)
    {
        this->pause();
        this->play();
    }
}

void Player::waitForLastRender()
{
    if (this->renderFuture.valid())
    {
        this->renderFuture.wait();
    }
    
    this->currentRenderIndex++;
    if (this->currentRenderIndex > 1)
    {
        this->currentRenderIndex = 0;
    }
}

void Player::startNextRender()
{
    this->renderFuture = std::async(&Player::asyncRenderFunction, this);
}

void Player::asyncRenderFunction()
{
    auto animationStack = this->model.getAnimationStack(this->currentAnimationStackIndex);
    if (animationStack == nullptr)
    {
        return;
    }
    
    const auto idx = this->currentRenderIndex;
    QSize renderImageSize;
    if (this->debuggerWidget)
    {
        renderImageSize = this->debuggerWidget->getRenderSegmentSize();
    }
    animationStack->renderStack(this->renderMemory[idx], renderImageSize);
}