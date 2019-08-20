#pragma once

#include "ui_DebuggerMainWindow.h"
#include "Player.h"

#include <QMainWindow>

class DebuggerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebuggerMainWindow(Player *player, QWidget *parent = 0);

private slots:
    void updateDebugger(AnimationStack &currentAnimation);
    void setFPSLabel(int fps);

private:
    Ui::DebuggerMainWindow ui;

    Player *player{ nullptr };
};
