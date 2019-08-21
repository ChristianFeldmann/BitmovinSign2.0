#pragma once

#include <QVector>
#include <QVariant>
#include <QAbstractItemModel>

class AnimationTreeItem
{
public:
    explicit AnimationTreeItem(const QVector<QVariant> &data, AnimationTreeItem *parent = nullptr);
    ~AnimationTreeItem();

    AnimationTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    AnimationTreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    QVector<AnimationTreeItem*> childItems;
    QVector<QVariant> itemData;
    AnimationTreeItem *parentItem;
};
