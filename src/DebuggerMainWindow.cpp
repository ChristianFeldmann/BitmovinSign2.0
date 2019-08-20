#pragma once

#include "DebuggerMainWindow.h"

DebuggerMainWindow::DebuggerMainWindow(Player *player, QWidget *parent) :
    QMainWindow(parent)
{
    this->player = player;
    
    this->ui.setupUi(this);
    
    connect(this->player, &Player::updateDebugger, this, &DebuggerMainWindow::updateDebugger);
    connect(this->player, &Player::updateFPS, this, &DebuggerMainWindow::setFPSLabel);
}

void DebuggerMainWindow::updateDebugger(AnimationStack &currentAnimation)
{
    this->ui.debuggerWidget->draw(currentAnimation);
}

void DebuggerMainWindow::setFPSLabel(int fps)
{
    this->ui.fpsLabel->setText(QString("%1 fps").arg(fps));
}
