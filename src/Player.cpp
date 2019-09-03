#include "Player.h"

#include "Constants.h"

#include <QDebug>
#include <QDomDocument>

Player::Player(QObject *parent) : QObject(parent)
{
    this->currentAnimationStackIndex = 0;
    
    connect(&this->fpsTimer, &QTimer::timeout, this, &Player::fpsTimerTimeout);
    this->fpsTimer.start(1000);

    playlist.createDefaultPlaylist();
    this->play();
}

void Player::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    auto animationStack = this->playlist.getAnimationStack(this->currentAnimationStackIndex);
    if (animationStack == nullptr)
    {
        return;
    }

    QStringList animationNames = animationStack->getChildAnimationNames();
    if (animationStack->renderStack(this->outputFrame, this->renderMemory))
    {
        static const int minimumAnimationRuntime = 500;
        if (autoSwitchStacks && currentAnimationRuntime > minimumAnimationRuntime)
        {
            this->currentAnimationStackIndex++;
            if (this->currentAnimationStackIndex >= this->playlist.childCount())
            {
                this->currentAnimationStackIndex = 0;
            }
            currentAnimationRuntime = 0;
            this->playlist.getAnimationStack(this->currentAnimationStackIndex)->resetAnimations();
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

void Player::setCurrentAnimation(AnimationTreeBase *item)
{
    int index = this->playlist.getAnimationStackIndex(item);
    if (index >= 0)
    {
        this->currentAnimationStackIndex = index;
        currentAnimationRuntime = 0;
        this->playlist.getAnimationStack(this->currentAnimationStackIndex)->resetAnimations();
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

bool Player::loadPlaylistFile(QString fileList)
{
    // TODO
    return false;
}

QString Player::getPlaylistString()
{
    // Create the XML document structure
    QDomDocument document;
    document.appendChild(document.createProcessingInstruction(QStringLiteral("xml"), QStringLiteral("version=\"1.0\" encoding=\"UTF-8\"")));
    QDomElement plist = document.createElement(QStringLiteral("playlistItems"));
    plist.setAttribute(QStringLiteral("version"), QStringLiteral("2.0"));
    document.appendChild(plist);

    this->playlist.savePlaylist(plist);

    return document.toString();
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
