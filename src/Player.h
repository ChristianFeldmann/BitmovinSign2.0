#pragma once

#include <QBasicTimer>
#include <QTimer>

#include "AnimationPlaylist.h"
#include "Frame.h"
#include "Output.h"
#include "DebuggerWidget.h"
#include "Constants.h"

#include <memory>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player(){};

    Player(const Player&) = delete;
    Player& operator =(const Player&) = delete;

signals:
    void updateDebugger(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory);
    void updateFPS(int fps);

private slots:
    void fpsTimerTimeout();
    
private:
    QBasicTimer timer;
    Output output;
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE; // Overloaded from QObject. Called when the timer fires.

    AnimationPlaylist playlist;
    unsigned currentAnimationStackIndex{ 0 };
    unsigned currentAnimationRuntime{ 0 };

    Frame outputFrame;
    RenderMemory renderMemory;
    
    QTimer fpsTimer;
    unsigned fpsDrawCounter{ 0 };
};
