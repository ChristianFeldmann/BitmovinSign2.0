#include "Player.h"

#include "Constants.h"

#include <QDebug>
#include <QDomDocument>

Player::Player(QObject *parent) : QObject(parent)
{
    this->currentAnimationStackIndex = 0;
    
    connect(&this->fpsTimer, &QTimer::timeout, this, &Player::fpsTimerTimeout);
    this->fpsTimer.start(1000);
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    auto animationStack = this->model.getAnimationStack(this->currentAnimationStackIndex);
    if (animationStack == nullptr)
    {
        return;
    }

    QStringList animationNames = animationStack->getChildAnimationNames();
    animationStack->renderStack(this->outputFrame, this->renderMemory);
    
    if (this->animationSwitchFrames > 0)
    {
        if (currentAnimationRuntime > this->animationSwitchFrames)
        {
            if (animationStack->getStackState() == AnimationState::Infinite)
            {
                fader.state = Fader::State::FadeOut;
            }
            else if (animationStack->getStackState() == AnimationState::SwitchNow)
            {
                this->switchToNextAnimation();
            }
        }
        
        currentAnimationRuntime++;
    }

    const unsigned fadeSpeed = 5;
    if (fader.state != Fader::State::NotFading)
    {
        if (fader.state == Fader::State::FadeIn)
        {
            this->fader.fadeValue += fadeSpeed;
            if (this->fader.fadeValue >= 255)
            {
                fader.state = Fader::State::NotFading;
            }
        }
        else // FadeOut
        {
            this->fader.fadeValue -= std::min(fadeSpeed, this->fader.fadeValue);
            if (this->fader.fadeValue == 0)
            {
                this->switchToNextAnimation();
                fader.state = Fader::State::FadeIn;
            }
        }
        
        this->outputFrame.scaleAlpha(this->fader.fadeValue);
    }

    emit this->updateDebugger(animationNames, &this->outputFrame, &this->renderMemory);
    this->output.pushData(this->outputFrame);
    
    this->fpsDrawCounter++;
}

void Player::switchToNextAnimation()
{
    this->currentAnimationStackIndex++;
    if (this->currentAnimationStackIndex >= unsigned(this->model.rowCount()))
    {
        this->currentAnimationStackIndex = 0;
    }
    currentAnimationRuntime = 0;
    this->model.getAnimationStack(this->currentAnimationStackIndex)->resetAnimations();
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
        this->animationSwitchFrames = 0;
    }
}

void Player::pause()
{
    this->timer.stop();
    this->playing = false;
}

void Player::play()
{
    auto animationStack = this->model.getAnimationStack(this->currentAnimationStackIndex);
    if (!animationStack)
    {
        qDebug() << "Notiong to play";
        return;
    }

    if (animationStack->getStackState() == AnimationState::Infinite)
    {
        this->fader.state = Fader::State::FadeIn;
    }

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

void Player::enableAnimationSwitch(unsigned timeoutSeconds)
{
    this->animationSwitchFrames = timeoutSeconds * 50;
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
