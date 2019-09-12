#include "AnimationTreeModel.h"

#include "AnimationTreeBase.h"
#include "AnimationStack.h"
#include "AnimationPlaylist.h"

#include <QBuffer>
#include <QColor>
#include <QDebug>
#include <QInputDialog>

const QString signMimeType = "application / bitmovinSignTreeModelItem";

AnimationTreeModel::AnimationTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

QModelIndex AnimationTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }

    auto parentItem = this->getItem(parent);
    auto childItem = parentItem->child(row);

    if (childItem == nullptr)
    {
        return QModelIndex();
    }
    
    return createIndex(row, column, childItem);
}

int AnimationTreeModel::rowCount(const QModelIndex &parent) const
{
    const AnimationTreeBase *parentItem = this->getItem(parent);
    return int(parentItem->childCount());
}

int AnimationTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant AnimationTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
    {
        return QVariant();
    }

    auto item = this->getItem(index);
    return item->data(index.column());
}

Qt::DropActions AnimationTreeModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::ItemFlags AnimationTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
    {
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    }
    return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList AnimationTreeModel::mimeTypes() const
{
    QStringList types;
    types << signMimeType;
    return types;
}

QMimeData *AnimationTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData;
    
    QDomDocument document;
    QDomElement plist = document.createElement("mimeData");
    document.appendChild(plist);
    for (const QModelIndex &index : indexes)
    {
        if (index.isValid()) 
        {
            AnimationTreeBase *item = static_cast<AnimationTreeBase*>(index.internalPointer());
            if (item)
            {
                if (!item->savePlaylist(plist))
                {
                    qDebug() << "Error saving tree item to playlist for mime data.";
                    return {};
                }
            }
        }
    }

    QString docString = document.toString();
    QByteArray encodedData = docString.toLatin1();

    mimeData->setData(signMimeType, encodedData);
    return mimeData;
}


bool AnimationTreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);

    if (!data->hasFormat(signMimeType) || (column > 0))
    {
        return false;
    }

    const AnimationTreeBase *parentItem = this->getItem(parent);
    if (parentItem == nullptr)
    {
        qDebug() << "cannot drop - no parent ";
        return false;
    }

    // We are always dropping onto the parent item
    // Row >= 0 means we are dropping before child "row" of the parent Item
    const AnimationTreeBase *dropItem = parentItem;
    
    // Try to open the mime data as DOM document
    QByteArray dataArray = data->data(signMimeType);
    QBuffer buffer(&dataArray);
    QDomDocument doc;
    QString errorMessage;
    int errorLine;
    int errorColumn;
    bool success = doc.setContent(&buffer, false, &errorMessage, &errorLine, &errorColumn);
    if (!success)
    {
        qDebug() << "canDropMimeData: Error loading mime data. Message " << errorMessage << " line " << errorLine << " column" << errorColumn;
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "mimeData")
    {
        qDebug() << "Error loading mime data. mimeData tag not found.";
        return false;
    }

    // Iterate over all items in the mime data
    QDomNode n = root.firstChild();
    if (n.isNull())
    {
        qDebug() << "Error loading mime data. No item to add found in mime data.";
        return false;
    }
    while (!n.isNull())
    {
        QDomElement elem = n.toElement();
        if (!dropItem->canDropItem(elem))
        {
            return false;
        }
        n = n.nextSibling();
    }
    
    return true;
}

bool AnimationTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent) || action == Qt::IgnoreAction)
    {
        return false;
    }

    AnimationTreeBase *dropItem = this->getItemNonConst(parent);
    if (dropItem == nullptr)
    {
        return nullptr;
    }

    // A row of >= 0 means we are appending into parent item just above the row "row"
    int beginRow = row;
    if (row < 0)
    {
        beginRow = int(dropItem->childCount());
    }
    
    qDebug() << "dropMimeData row " << row;

    // Try to open the mime data as DOM document
    QByteArray dataArray = data->data(signMimeType);
    QBuffer buffer(&dataArray);
    QDomDocument doc;
    QString errorMessage;
    int errorLine;
    int errorColumn;
    bool success = doc.setContent(&buffer, false, &errorMessage, &errorLine, &errorColumn);
    if (!success)
    {
        qDebug() << "dropMimeData: Error loading mime data. Message " << errorMessage << " line " << errorLine << " column" << errorColumn;
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "mimeData")
    {
        qDebug() << "dropMimeData: Error loading mime data. mimeData tag not found.";
        return false;
    }

    QDomNode n = root.firstChild();
    if (n.isNull())
    {
        qDebug() << "dropMimeData: Error loading mime data. No item to add found in mime data.";
        return false;
    }

    unsigned int nrItemsToAdd = 0;
    while (!n.isNull())
    {
        if (n.isElement())
        {
            nrItemsToAdd++;
        }
        n = n.nextSibling();
    }

    beginInsertRows(parent, beginRow, beginRow + nrItemsToAdd - 1);
    qDebug() << "Insert beginRow " << beginRow << " nrItems " << nrItemsToAdd;

    auto stack = dynamic_cast<AnimationStack*>(dropItem);
    AnimationPlaylist *playlist = dynamic_cast<AnimationPlaylist*>(dropItem);
    
    n = root.firstChild();
    int position = beginRow;
    while (!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement elem = n.toElement();
            if (stack)
            {
                stack->addAnimationFromDomElement(elem, position);
                qDebug() << "Adding animation at position " << position;
            }
            else if (playlist)
            {
                playlist->addStackFromDomElement(elem, position);
                qDebug() << "Adding animation at position " << position;
            }
            position++;
        }
        n = n.nextSibling();
    }

    endInsertRows();

    return true;
}

const AnimationTreeBase *AnimationTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid())
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(index.internalPointer());
        if (item)
        {
            return item;
        }
    }
    return &this->playlist;
}

AnimationTreeBase *AnimationTreeModel::getItemNonConst(const QModelIndex &index)
{
    if (index.isValid())
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(index.internalPointer());
        if (item)
        {
            return item;
        }
    }
    return &this->playlist;
}

bool AnimationTreeModel::loadPlaylistFile(QString filePath)
{
    beginResetModel();
    bool success = this->playlist.loadPlaylistFile(filePath);
    endResetModel();
    return success;
}

bool AnimationTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    auto parentItem = getItemNonConst(parent);
    if (position == -1)
    {
        parentItem->childCount();
    }
    
    auto stack = dynamic_cast<AnimationStack*>(parentItem);
    if (stack)
    {
        auto animationList = AnimationStack::getAnimationList();
        QString selection = QInputDialog::getItem(nullptr, "Add animation", "Please choose the type of animation", animationList);
        if (!animationList.contains(selection))
        {
            return false;
        }
        beginInsertRows(parent, position, position + rows - 1);
        bool success = stack->insertAnimation(position, selection);
        endInsertRows();
        return success;
    }
    
    AnimationPlaylist *playlist = dynamic_cast<AnimationPlaylist*>(parentItem);
    if (playlist)
    {
        
        beginInsertRows(parent, position, position + rows - 1);
        bool success = playlist->insertStack(position);
        endInsertRows();
        return success;
    }

    return false;
}

bool AnimationTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    auto parentItem = getItemNonConst(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

QModelIndex AnimationTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    auto childItem = getItem(index);
    auto parentItem = childItem->getParent();

    if (parentItem == &this->playlist || parentItem == nullptr)
    {
        return QModelIndex();
    }

    auto grandparentItem = parentItem->getParent();
    if (grandparentItem == nullptr)
    {
        return QModelIndex();
    }

    const int row = grandparentItem->childNumber(parentItem);
    return createIndex(row, 0, parentItem);
}
