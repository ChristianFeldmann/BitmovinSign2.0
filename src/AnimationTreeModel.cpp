#include "AnimationTreeModel.h"

#include "AnimationTreeBase.h"
#include "AnimationStack.h"
#include "AnimationPlaylist.h"

#include <QColor>
#include <QInputDialog>

AnimationTreeModel::AnimationTreeModel(AnimationTreeBase *treeRoot, QObject *parent) :
    QAbstractItemModel(parent)
{
    this->rootItem = treeRoot;
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
    AnimationTreeBase *parentItem = getItem(parent);
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

AnimationTreeBase *AnimationTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) 
    {
        AnimationTreeBase *item = static_cast<AnimationTreeBase*>(index.internalPointer());
        if (item)
        {
            return item;
        }
    }
    return this->rootItem;
}

//QVariant AnimationTreeModel::headerData(int section, Qt::Orientation orientation,
//    int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//    {
//        return rootItem.data(section);
//    }
//
//    return QVariant();
//}

bool AnimationTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    auto parentItem = getItem(parent);
    if (position == -1)
    {
        parentItem->childCount();
    }
    
    AnimationStack *stack = dynamic_cast<AnimationStack*>(parentItem);
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
    auto parentItem = getItem(parent);
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

    if (parentItem == rootItem || parentItem == nullptr)
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
