#pragma once

#include <QBasicTimer>
#include <QTimer>

#include "AnimationPlaylist.h"
#include "AnimationTreeModel.h"
#include "Frame.h"
#include "Output.h"
#include "DebuggerWidget.h"
#include "Constants.h"
#include "RenderMemory.h"

#include <future>
#include <memory>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player(){};

    Player(const Player&) = delete;
    Player& operator =(const Player&) = delete;

    void setCurrentAnimation(AnimationTreeBase *item);

    void pause();
    void play();
    void step();

    bool isPlaying() { return this->playing; }

    bool loadPlaylistFile(QString filePath);
    QString getPlaylistString() { return this->model.getPlaylistString(); }

    AnimationTreeModel *getAnimationTreeMode() { return &this->model; }

public slots:
    void setTargetFPS(int value);

signals:
    void updateDebugger(QStringList animationNames, RenderMemory *renderMemory);
    void updateFPS(int fps);

private slots:
    void fpsTimerTimeout();
    
private:
    QBasicTimer timer;
    int targetFPS{ 50 };

    Output output;
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE; // Overloaded from QObject. Called when the timer fires.

    unsigned currentAnimationStackIndex{ 0 };
    unsigned currentAnimationRuntime{ 0 };

    RenderMemory renderMemory[2];
    unsigned currentRenderIndex{ 0 };
    std::future<void> renderFuture;
    void waitForLastRender();
    void startNextRender();
    void asyncRenderFunction();
    
    QTimer fpsTimer;
    unsigned fpsDrawCounter{ 0 };

    bool autoSwitchStacks{ false };
    bool playing{ false };

    AnimationTreeModel model;
};
