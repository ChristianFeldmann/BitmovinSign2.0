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
    void updateDebugger(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory);
    void setFPSLabel(int fps);
    void viewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Ui::DebuggerMainWindow ui;

    QWidget emptyPropertiesWidget;

    Player *player{ nullptr };
};
