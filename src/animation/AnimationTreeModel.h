#pragma once

#include "AnimationTreeBase.h"
#include "AnimationPlaylist.h"

#include <QAbstractItemModel>
#include <QMimeData>

class AnimationTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AnimationTreeModel(QObject *parent = 0);
    ~AnimationTreeModel() = default;
    
    // Needed for a read only model
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Qt::DropActions supportedDropActions() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    int getAnimationStackIndex(AnimationTreeBase *stack) const { return this->playlist.getAnimationStackIndex(stack); }
    std::shared_ptr<AnimationStack> getAnimationStack(unsigned index) const { return this->playlist.getAnimationStack(index); }
    
    bool loadPlaylistFile(QString filePath);
    QString getPlaylistString() const { return this->playlist.getPlaylistString(); }
    bool createDefaultPlaylist() { return this->playlist.createDefaultPlaylist(); }
    
    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

    bool insertNewAnimation(int position, int rows, QString animationType, const QModelIndex &parent = QModelIndex());
    bool insertNewStack(int position, int rows, const QModelIndex &parent = QModelIndex());

    AnimationTreeBase *getItemNonConst(const QModelIndex &index);

private:
    const AnimationTreeBase *getItem(const QModelIndex &index) const;

    AnimationPlaylist playlist;
};
