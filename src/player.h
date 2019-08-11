#pragma once

#include <QBasicTimer>

#include "AnimationInterface.h"
#include "AnimationHandler.h"
#include "Output.h"
#include "DebuggerWidget.h"

#include <memory>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player(){};

    Player(const Player&) = delete;
    Player& operator =(const Player&) = delete;

    void set_output(Output *output);
    void set_debugger(DebuggerWidget *debugger);

private:
    QBasicTimer timer;
    Output *output{nullptr};
    DebuggerWidget *debugger;
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE; // Overloaded from QObject. Called when the timer fires.

    std::vector<std::unique_ptr<AnimationInterface>> animationStack;
    AnimationHandler animationHandler;
};

