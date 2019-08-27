#include "AnimationTreeModel.h"

#include "AnimationTreeBase.h"
#include "AnimationStack.h"

#include <QColor>

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
    return 2;
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

//Qt::ItemFlags AnimationTreeModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//    {
//        return 0;
//    }
//
//    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
//}

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
//
//
//
//bool AnimationTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;
//
//    beginInsertColumns(parent, position, position + columns - 1);
//    success = rootItem.insertColumns(position, columns);
//    endInsertColumns();
//
//    return success;
//}
//
//bool AnimationTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
//{
//    auto parentItem = getItem(parent);
//    bool success;
//
//    beginInsertRows(parent, position, position + rows - 1);
//    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
//    endInsertRows();
//
//    return success;
//}
//
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

//
//bool AnimationTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
//{
//    bool success;
//
//    beginRemoveColumns(parent, position, position + columns - 1);
//    success = rootItem.removeColumns(position, columns);
//    endRemoveColumns();
//
//    if (rootItem.columnCount() == 0)
//    {
//        removeRows(0, rowCount());
//    }
//
//    return success;
//}
//
//bool AnimationTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
//{
//    auto parentItem = getItem(parent);
//    bool success = true;
//
//    beginRemoveRows(parent, position, position + rows - 1);
//    success = parentItem->removeChildren(position, rows);
//    endRemoveRows();
//
//    return success;
//}
//
//
//bool AnimationTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (role != Qt::EditRole)
//    {
//        return false;
//    }
//
//    AnimationTreeItem *item = getItem(index);
//    bool result = item->setData(index.column(), value);
//
//    if (result)
//    {
//        emit dataChanged(index, index, { role });
//    }
//
//    return result;
//}
//
//bool AnimationTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (role != Qt::EditRole || orientation != Qt::Horizontal)
//    {
//        return false;
//    }
//
//    bool result = rootItem->setData(section, value);
//
//    if (result)
//    {
//        emit headerDataChanged(orientation, section, section);
//    }
//
//    return result;
//}
//
//void AnimationTreeModel::setupModelData(const QStringList &lines, AnimationTreeItem *parent)
//{
//    QList<AnimationTreeItem*> parents;
//    QList<int> indentations;
//    parents << parent;
//    indentations << 0;
//
//    int number = 0;
//
//    while (number < lines.count()) 
//    {
//        int position = 0;
//        while (position < lines[number].length()) 
//        {
//            if (lines[number].at(position) != ' ')
//            {
//                break;
//            }
//            ++position;
//        }
//
//        QString lineData = lines[number].mid(position).trimmed();
//
//        if (!lineData.isEmpty()) 
//        {
//            // Read the column data from the rest of the line.
//            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
//            QVector<QVariant> columnData;
//            for (int column = 0; column < columnStrings.count(); ++column)
//            {
//                columnData << columnStrings[column];
//            }
//
//            if (position > indentations.last()) 
//            {
//                // The last child of the current parent is now the new parent
//                // unless the current parent has no children.
//
//                if (parents.last()->childCount() > 0) 
//                {
//                    parents << parents.last()->child(parents.last()->childCount() - 1);
//                    indentations << position;
//                }
//            }
//            else 
//            {
//                while (position < indentations.last() && parents.count() > 0) 
//                {
//                    parents.pop_back();
//                    indentations.pop_back();
//                }
//            }
//
//            // Append a new item to the current parent's list of children.
//            AnimationTreeItem *parent = parents.last();
//            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
//            for (int column = 0; column < columnData.size(); ++column)
//            {
//                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
//            }
//        }
//
//        ++number;
//    }
//}