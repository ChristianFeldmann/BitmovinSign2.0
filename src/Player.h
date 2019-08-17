#pragma once

#include <QBasicTimer>
#include <QTimer>

#include "AnimationInterface.h"
#include "AnimationStack.h"
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

    void set_debugger(DebuggerWidget *debugger);

private:
    QBasicTimer timer;
    Output output;
    DebuggerWidget *debugger;
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE; // Overloaded from QObject. Called when the timer fires.

    AnimationStack currentAnimation;
    unsigned currentAnimationRuntime{ 0 };
};
