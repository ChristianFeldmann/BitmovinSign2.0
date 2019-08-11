#pragma once

#include <QBasicTimer>

#include <AnimationInterface.h>
#include <Output.h>
#include <DebuggerWidget.h>
#include <Constants.h>

#include <memory>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(AnimationList animationList, QObject *parent = nullptr);
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

    AnimationList animationList;
    unsigned currentAnimation{0};
};
