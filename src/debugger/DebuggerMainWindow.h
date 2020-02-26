#pragma once

#include "ui_DebuggerMainWindow.h"
#include "common/Player.h"

#include <QMainWindow>
#include <QAction>
#include <QPointer>

class DebuggerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebuggerMainWindow(Player *player, QWidget *parent = 0);

    void closeEvent(QCloseEvent *event) override;

private slots:
    void updateDebugger(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory);
    void setFPSLabel(int fps);
    void viewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void onPlayPausePushButton();
    void onStepPushButton();
    
    void onTreeViewCustomContextMenu(const QPoint &point);
    void addItem();
    void deleteItem();

    void showFileOpenDialog();
    void savePlaylistToFile();
    void openRecentFile();

private:
    Ui::DebuggerMainWindow ui;

    QWidget emptyPropertiesWidget;

    Player *player{ nullptr };

    QModelIndex currentItemContextMenu;

    // We save the recent file actions so that we can change them (their text) later
    QPointer<QAction> recentFileActions[MAX_RECENT_FILES];
    void updateRecentFileActions();

    bool isSaved{ true };
    void loadFiles(QStringList files);
};
