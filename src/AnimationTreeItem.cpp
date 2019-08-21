#include "AnimationTreeItem.h"

AnimationTreeItem::AnimationTreeItem(const QVector<QVariant> &data, AnimationTreeItem *parent)
    : itemData(data),
    parentItem(parent)
{
}

AnimationTreeItem::~AnimationTreeItem()
{
    qDeleteAll(childItems);
}

AnimationTreeItem *AnimationTreeItem::parent()
{
    return parentItem;
}

AnimationTreeItem *AnimationTreeItem::child(int number)
{
    if (number < 0 || number >= childItems.size())
    {
        return nullptr;
    }
    return childItems.at(number);
}

int AnimationTreeItem::childCount() const
{
    return childItems.count();
}

int AnimationTreeItem::childNumber() const
{
    if (parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<AnimationTreeItem*>(this));
    }
    return 0;
}

int AnimationTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant AnimationTreeItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
    {
        return QVariant();
    }
    return itemData.at(column);
}

bool AnimationTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
    {
        return false;
    }

    for (int column = 0; column < columns; ++column)
    {
        itemData.remove(position);
    }

    for (AnimationTreeItem *child: childItems)
    {
        child->removeColumns(position, columns);
    }

    return true;
}


bool AnimationTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
    {
        return false;
    }

    itemData[column] = value;
    return true;
}

bool AnimationTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
    {
        return false;
    }

    for (int row = 0; row < count; ++row) 
    {
        QVector<QVariant> data(columns);
        AnimationTreeItem *item = new AnimationTreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool AnimationTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
    {
        return false;
    }

    for (int row = 0; row < count; ++row)
    {
        delete childItems.takeAt(position);
    }

    return true;
}

bool AnimationTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
    {
        return false;
    }

    for (int column = 0; column < columns; ++column)
    {
        itemData.insert(position, QVariant());
    }

    for (AnimationTreeItem *child : qAsConst(childItems))
    {
        child->insertColumns(position, columns);
    }

    return true;
}

