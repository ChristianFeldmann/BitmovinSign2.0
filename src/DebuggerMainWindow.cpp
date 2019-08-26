#pragma once

#include "DebuggerMainWindow.h"
#include "AnimationTreeModel.h"

#include <QFile>

DebuggerMainWindow::DebuggerMainWindow(Player *player, QWidget *parent) :
    QMainWindow(parent)
{
    this->player = player;
    
    this->ui.setupUi(this);
    
    connect(this->player, &Player::updateDebugger, this, &DebuggerMainWindow::updateDebugger);
    connect(this->player, &Player::updateFPS, this, &DebuggerMainWindow::setFPSLabel);

    {
        QStringList headers;
        headers << tr("Title") << tr("Description");

        QFile file("default.txt");
        file.open(QIODevice::ReadOnly);
        AnimationTreeModel *model = new AnimationTreeModel();
        file.close();

        this->ui.animationStacksView->setModel(model);

        for (int column = 0; column < model->columnCount(); ++column)
        {
            this->ui.animationStacksView->resizeColumnToContents(column);
        }
        this->ui.animationStacksView->setStyleSheet(QString("QTreeView { show-decoration-selected: 1; }"));
    }
}

void DebuggerMainWindow::updateDebugger(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory)
{
    this->ui.debuggerWidget->draw(animationNames, outputFrame, renderMemory);
}

void DebuggerMainWindow::setFPSLabel(int fps)
{
    this->ui.fpsLabel->setText(QString("%1 fps").arg(fps));
}
