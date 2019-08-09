#pragma once

#include <QBasicTimer>

#include "../animations/animationInterface.h"
#include "debugger_widget.h"

class Player : public QObject
{
    Q_OBJECT

private:
    /* data */
    QBasicTimer timer;
    animationInterface *animation{nullptr};
    debugger_widget *debugger;
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE; // Overloaded from QObject. Called when the timer fires.

public:
    Player(QObject *parent = nullptr);
    ~Player(){};

    void set_animation(animationInterface *animation);
    void set_debugger(debugger_widget *debugger);
};

