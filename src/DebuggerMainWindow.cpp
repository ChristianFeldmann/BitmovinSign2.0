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
        AnimationTreeModel *model = new AnimationTreeModel(player->getPlaylist());
        file.close();

        this->ui.animationStacksView->setModel(model);

        for (int column = 0; column < model->columnCount(); ++column)
        {
            this->ui.animationStacksView->resizeColumnToContents(column);
        }
        this->ui.animationStacksView->setStyleSheet(QString("QTreeView { show-decoration-selected: 1; }"));
    }

    auto selectionModel = this->ui.animationStacksView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &DebuggerMainWindow::viewSelectionChanged);

    this->ui.stackedWidgetProperties->addWidget(&this->emptyPropertiesWidget);
    this->ui.stackedWidgetProperties->setCurrentWidget(&this->emptyPropertiesWidget);
}

void DebuggerMainWindow::updateDebugger(QStringList animationNames, Frame *outputFrame, RenderMemory *renderMemory)
{
    this->ui.debuggerWidget->draw(animationNames, outputFrame, renderMemory);
}

void DebuggerMainWindow::setFPSLabel(int fps)
{
    this->ui.fpsLabel->setText(QString("%1 fps").arg(fps));
}

void DebuggerMainWindow::viewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    auto indexes = selected.indexes();
    if (indexes.size() == 1)
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(indexes[0].internalPointer());

        if (item)
        {
            this->player->setCurrentAnimation(item);
            QWidget *propertiesWidget = item->getPropertiesWidget();
            if (this->ui.stackedWidgetProperties->indexOf(propertiesWidget) == -1)
            {
                this->ui.stackedWidgetProperties->addWidget(propertiesWidget);
            }
            this->ui.stackedWidgetProperties->setCurrentWidget(propertiesWidget);
            return;
        }
    }

    this->ui.stackedWidgetProperties->setCurrentWidget(&this->emptyPropertiesWidget);
}
