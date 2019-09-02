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

    void onPlayPausePushButton();
    void onStepPushButton();
    
    void onTreeViewCustomContextMenu(const QPoint &point);
    void addItem();
    void deleteItem();

private:
    Ui::DebuggerMainWindow ui;

    QWidget emptyPropertiesWidget;

    Player *player{ nullptr };

    QModelIndex currentItemContextMenu;
};
