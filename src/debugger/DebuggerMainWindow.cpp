#include "DebuggerMainWindow.h"

#include "animation/AnimationTreeModel.h"

#include <QCloseEvent>
#include <QComboBox>
#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QVBoxLayout>

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

        this->ui.animationStacksView->setModel(player->getAnimationTreeMode());
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

    // Create the menu
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction("&Open File...", this, &DebuggerMainWindow::showFileOpenDialog, Qt::CTRL + Qt::Key_O);
    QMenu *recentFileMenu = fileMenu->addMenu("Recent Files");
    for (int i = 0; i < MAX_RECENT_FILES; i++)
    {
        recentFileActions[i] = new QAction(this);
        connect(recentFileActions[i].data(), &QAction::triggered, this, &DebuggerMainWindow::openRecentFile);
        recentFileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction("&Save Playlist...", this, &DebuggerMainWindow::savePlaylistToFile, Qt::CTRL + Qt::Key_S);

    this->ui.animationStacksView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui.animationStacksView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui.animationStacksView->setDragEnabled(true);
    this->ui.animationStacksView->setAcceptDrops(true);
    this->ui.animationStacksView->setDropIndicatorShown(true);
    this->ui.animationStacksView->setHeaderHidden(true);

    this->ui.debuggerWidget->setDrawMode(DebuggerWidget::DrawMode::MultipleAnimations);
}

void DebuggerMainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    if (!this->isSaved)
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Quit YUView",
            tr("You have not saved the current playlist, are you sure?\n"),
            QMessageBox::Cancel | QMessageBox::Close | QMessageBox::Save,
            QMessageBox::Close);
        if (resBtn == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
        else if (resBtn == QMessageBox::Save)
        {
            this->savePlaylistToFile();
        }
    }

    event->accept();
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
            if (item->propertiesWidgetIndex == -1)
            {
                QWidget *propertiesWidget = createPropertiesWidgetForTreeItem(item);
                item->propertiesWidgetIndex = this->ui.stackedWidgetProperties->addWidget(propertiesWidget);
            }
            this->ui.stackedWidgetProperties->setCurrentIndex(item->propertiesWidgetIndex);
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
    size_t row;
    if (this->currentItemContextMenu.isValid())
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(this->currentItemContextMenu.internalPointer());
        row = item->childCount();
    }
    else
    {
        row = this->player->getAnimationTreeMode()->rowCount();
    }

    auto parentItem = this->player->getAnimationTreeMode()->getItemNonConst(this->currentItemContextMenu);
    auto stack = dynamic_cast<AnimationStack*>(parentItem);
    if (stack)
    {
        auto animationList = AnimationStack::getAnimationList();
        QString selection = QInputDialog::getItem(nullptr, "Add animation", "Please choose the type of animation", animationList);
        if (!animationList.contains(selection))
        {
            return;
        }
        this->player->getAnimationTreeMode()->insertNewAnimation(int(row), 1, selection, this->currentItemContextMenu);
        return;
    }

    AnimationPlaylist *playlist = dynamic_cast<AnimationPlaylist*>(parentItem);
    if (playlist)
    {
        this->player->getAnimationTreeMode()->insertNewStack(int(row), 1, this->currentItemContextMenu);
        return;
    }

    this->ui.animationStacksView->model()->insertRow(int(row), this->currentItemContextMenu);
}

void DebuggerMainWindow::deleteItem()
{
    if (this->currentItemContextMenu.isValid())
    {
        int row = this->currentItemContextMenu.row();
        this->ui.animationStacksView->model()->removeRow(row, this->currentItemContextMenu.parent());
    }
}

void DebuggerMainWindow::showFileOpenDialog()
{
    QSettings settings;
    QStringList filters = QStringList() << "*.signPlaylist";

    QFileDialog openDialog(this);
    openDialog.setDirectory(settings.value("lastFilePath").toString());
    openDialog.setFileMode(QFileDialog::ExistingFiles);
    openDialog.setNameFilters(filters);

    QStringList fileNames;
    if (openDialog.exec())
    {
        fileNames = openDialog.selectedFiles();
        if (fileNames.count() > 0)
        {
            QString filePath = fileNames.at(0);
            filePath = filePath.section('/', 0, -2);
            settings.setValue("lastFilePath", filePath);
            this->loadFiles(fileNames);
        }
    }

    updateRecentFileActions();
}

void DebuggerMainWindow::savePlaylistToFile()
{
    // ask user for file location
    QSettings settings;

    QString filename = QFileDialog::getSaveFileName(this, tr("Save Playlist"), settings.value("LastPlaylistPath").toString(), tr("Playlist Files (*.signPlaylist)"));
    if (filename.isEmpty())
        return;
    if (!filename.endsWith(".signPlaylist", Qt::CaseInsensitive))
        filename += ".signPlaylist";

    // remember this directory for next time
    QDir dirName(filename.section('/', 0, -2));
    settings.setValue("LastPlaylistPath", dirName.path());

    // Write the XML structure to file
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&file);
    outStream << this->player->getPlaylistString();
    file.close();

    // We saved the playlist
    this->isSaved = true;
}

void DebuggerMainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (action)
    {
        QStringList fileList = QStringList(action->data().toString());
        this->loadFiles(fileList);
    }
}

void DebuggerMainWindow::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = std::min(files.size(), int(MAX_RECENT_FILES));

    int fileIdx = 0;
    for (int i = 0; i < numRecentFiles; ++i)
    {
        if (!(QFile(files[i]).exists()))
        {
            continue;
        }

        //QString text = tr("&%1 %2").arg(fileIdx++).arg(QFileInfo(files[i]).fileName());
        QString text = tr("&%1 %2").arg(fileIdx + 1).arg(files[i]);
        recentFileActions[fileIdx]->setText(text);
        recentFileActions[fileIdx]->setData(files[i]);
        recentFileActions[fileIdx]->setVisible(true);

        fileIdx++;
    }
    for (int j = fileIdx; j < MAX_RECENT_FILES; ++j)
    {
        recentFileActions[j]->setVisible(false);
    }
}

void DebuggerMainWindow::loadFiles(QStringList filesToOpen)
{
    for (auto filePath : filesToOpen)
    {
        QFileInfo fi(filePath);

        QString ext = fi.suffix().toLower();
        if (ext == "signplaylist")
        {
            // Load the playlist
            if (this->player->loadPlaylistFile(filePath))
            {
                // Add the playlist file as one of the recently opened files.
                QSettings settings;
                QStringList files = settings.value("recentFileList").toStringList();
                files.removeAll(filePath);
                files.prepend(filePath);
                while (files.size() > MAX_RECENT_FILES)
                {
                    files.removeLast();
                }

                settings.setValue("recentFileList", files);
            }
        }
    }
}

QWidget *DebuggerMainWindow::createPropertiesWidgetForTreeItem(AnimationTreeBase *item)
{
    QWidget *propertiesWidget = new QWidget;
    propertiesWidget->setObjectName(item->getWidgetName());

    auto animations = item->getAnimationParameters();
    if (animations.empty())
    {
        QVBoxLayout *vAllLaout = new QVBoxLayout(propertiesWidget);
        QLabel *label = new QLabel(nullptr);
        label->setText("No properties");
        vAllLaout->addWidget(label);
        vAllLaout->insertStretch(2, 1);
    }
    else
    {
        QFormLayout *form = new QFormLayout(propertiesWidget);
        for (auto parameter : animations)
        {
            QWidget *newParameterWidget = nullptr;
            if (parameter->type == AnimationParameter::Type::Enum)
            {
                auto enumComboBox = new QComboBox();
                for (auto &enumItem : parameter->enumValues)
                {
                    enumComboBox->addItem(enumItem);
                }
                connect(enumComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DebuggerMainWindow::onEnumComboBoxIndexChanged);
                controlToParameterMap[enumComboBox] = parameter;
                newParameterWidget = enumComboBox;
            }
            else if (parameter->type == AnimationParameter::Type::Int || parameter->type == AnimationParameter::Type::UInt)
            {
                auto intSpinBox = new QSpinBox();
                if (parameter->type == AnimationParameter::Type::Int)
                {
                    intSpinBox->setValue(*parameter->integer);
                    intSpinBox->setRange(0, 10000);
                }
                else
                {
                    intSpinBox->setValue(*parameter->unsignedInt);
                    intSpinBox->setRange(-10000, 10000);
                }
                connect(intSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &DebuggerMainWindow::onIntSpinBoxValueChanged);
                controlToParameterMap[intSpinBox] = parameter;
                newParameterWidget = intSpinBox;
            }
            else if (parameter->type == AnimationParameter::Type::Float)
            {
                auto doubleSpinBox = new QDoubleSpinBox();
                doubleSpinBox->setValue(*parameter->floatValue);
                doubleSpinBox->setRange(-1000.0, 1000.0);
                connect(doubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DebuggerMainWindow::onDoubleSpinBoxValueChanged);
                controlToParameterMap[doubleSpinBox] = parameter;
                newParameterWidget = doubleSpinBox;
            }
            else if (parameter->type == AnimationParameter::Type::Color)
            {
                auto colorPushButton = new QPushButton();
                setColorForButton(colorPushButton, *parameter->color);
                connect(colorPushButton, &QPushButton::clicked, this, &DebuggerMainWindow::onColorButtonPressed);
                controlToParameterMap[colorPushButton] = parameter;
                newParameterWidget = colorPushButton;
            }
            else
            {
                newParameterWidget = new QLabel("Error");
            }

            form->addRow(parameter->name, newParameterWidget);
        }
    }
    
    return propertiesWidget;
}

void DebuggerMainWindow::onEnumComboBoxIndexChanged(int index)
{
    QObject *sender = QObject::sender();
    if (this->controlToParameterMap.contains(sender))
    {
        auto parameter = this->controlToParameterMap[sender];
        parameter->setEnumIndex(index);
    }
}

void DebuggerMainWindow::onColorButtonPressed(bool checked)
{
    Q_UNUSED(checked);
    QObject *sender = QObject::sender();
    if (this->controlToParameterMap.contains(sender))
    {
        auto parameter = this->controlToParameterMap[sender];
        QColor newColor = QColorDialog::getColor(*parameter->color, nullptr, "Please choose a new color", QColorDialog::ShowAlphaChannel);
        if (newColor.isValid())
        {
            parameter->setColor(newColor);
            QPushButton *button = dynamic_cast<QPushButton*>(sender);
            if (button)
            {
                setColorForButton(button, newColor);
            }
        }
    }
}

void DebuggerMainWindow::onIntSpinBoxValueChanged(int value)
{
    QObject *sender = QObject::sender();
    if (this->controlToParameterMap.contains(sender))
    {
        auto parameter = this->controlToParameterMap[sender];
        parameter->setInt(value);
    }
}

void DebuggerMainWindow::onDoubleSpinBoxValueChanged(double value)
{
    QObject *sender = QObject::sender();
    if (this->controlToParameterMap.contains(sender))
    {
        auto parameter = this->controlToParameterMap[sender];
        parameter->setFloat(float(value));
    }
}

void DebuggerMainWindow::setColorForButton(QPushButton *button, QColor newColor)
{
    QImage image(50, 50, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.fillRect(0, 0, 50, 50, newColor);
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    QIcon ico(pixmap);
    button->setIcon(ico);
}
