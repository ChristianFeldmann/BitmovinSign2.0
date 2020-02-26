#pragma once

#include <QBasicTimer>
#include <QTimer>

#include "animation/AnimationPlaylist.h"
#include "animation/AnimationTreeModel.h"
#include "common/Frame.h"
#include "common/Output.h"
#include "common/Constants.h"

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
    void play(bool enableFPSOutput = false);
    void step();

    bool isPlaying() { return this->playing; }

    bool loadPlaylistFile(QString filePath);
    QString getPlaylistString() { return this->model.getPlaylistString(); }
    bool createDefaultPlaylist() { return this->model.createDefaultPlaylist(); }

    AnimationTreeModel *getAnimationTreeMode() { return &this->model; }
    void enableAnimationSwitch(unsigned timeoutSeconds = 60);

public slots:
    void setTargetFPS(int value);

signals:
    void updateDebugger(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory);
    void updateFPS(int fps);

private slots:
    void fpsTimerTimeout();
    
private:
    QBasicTimer timer;
    int targetFPS{ 50 };

    Output output;
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE; // Overloaded from QObject. Called when the timer fires.
    void switchToNextAnimation();

    unsigned currentAnimationStackIndex{ 0 };
    unsigned currentAnimationRuntime{ 0 };
    unsigned animationSwitchFrames{ 0 };

    Frame outputFrame;
    RenderMemory renderMemory;
    
    QTimer fpsTimer;
    unsigned fpsDrawCounter{ 0 };

    bool playing{ false };

    struct Fader
    {
        enum class State
        {
            FadeIn,
            FadeOut,
            NotFading
        };
        State state { State::NotFading };
        unsigned fadeValue {0};
    };
    Fader fader;

    AnimationTreeModel model;
};
