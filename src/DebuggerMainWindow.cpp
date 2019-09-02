#pragma once

#include "DebuggerMainWindow.h"
#include "AnimationTreeModel.h"

#include <QFile>
#include <QDebug>

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

    this->ui.animationStacksView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->ui.animationStacksView, &QWidget::customContextMenuRequested, this, &DebuggerMainWindow::onTreeViewCustomContextMenu);

    connect(this->ui.pushButtonPlayPause, &QPushButton::clicked, this, &DebuggerMainWindow::onPlayPausePushButton);
    connect(this->ui.pushButtonStep, &QPushButton::clicked, this, &DebuggerMainWindow::onStepPushButton);
    connect(this->ui.targetFramerateSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this->player, &Player::setTargetFPS);
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

void DebuggerMainWindow::onPlayPausePushButton()
{
    if (this->player->isPlaying())
    {
        this->ui.pushButtonPlayPause->setText("Play");
        this->player->pause();
    }
    else
    {
        this->ui.pushButtonPlayPause->setText("Pause");
        this->player->play();
    }
}

void DebuggerMainWindow::onStepPushButton()
{
    this->player->step();
}

void DebuggerMainWindow::onTreeViewCustomContextMenu(const QPoint &point)
{
    QModelIndex index = this->ui.animationStacksView->indexAt(point);
    this->currentItemContextMenu = QModelIndex();

    if (index.isValid())
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(index.internalPointer());
        if (item != nullptr)
        {
            AnimationStack *stack = dynamic_cast<AnimationStack*>(item);
            if (stack)
            {
                QMenu *menu = new QMenu(this);
                menu->addAction("Delete Stack", this, &DebuggerMainWindow::deleteItem);
                menu->addAction("Add animation", this, &DebuggerMainWindow::addItem);
                menu->popup(this->ui.animationStacksView->viewport()->mapToGlobal(point));
                this->currentItemContextMenu = index;
                return;
            }
            AnimationBase *animation = dynamic_cast<AnimationBase*>(item);
            if (animation)
            {
                QMenu *menu = new QMenu(this);
                menu->addAction("Delete Animation", this, &DebuggerMainWindow::deleteItem);
                menu->popup(this->ui.animationStacksView->viewport()->mapToGlobal(point));
                this->currentItemContextMenu = index;
                return;
            }
        }
    }
    else
    {
        QMenu *menu = new QMenu(this);
        menu->addAction("Add Stack", this, &DebuggerMainWindow::addItem);
        menu->popup(this->ui.animationStacksView->viewport()->mapToGlobal(point));
    }
}

void DebuggerMainWindow::addItem()
{
    qDebug() << "Add item";

    size_t row;
    if (this->currentItemContextMenu.isValid())
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(this->currentItemContextMenu.internalPointer());
        row = item->childCount();
    }
    else
    {
        row = this->player->getPlaylist()->childCount();
    }
    this->ui.animationStacksView->model()->insertRow(int(row), this->currentItemContextMenu);
}

void DebuggerMainWindow::deleteItem()
{
    qDebug() << "Delete item";

    auto view = this->ui.animationStacksView;
    QModelIndex index = view->selectionModel()->currentIndex();

    if (this->currentItemContextMenu.isValid())
    {
        int row = this->currentItemContextMenu.row();
        this->ui.animationStacksView->model()->removeRow(row, this->currentItemContextMenu.parent());
    }
}
