#pragma once

#include "AnimationTreeBase.h"
#include "AnimationPlaylist.h"

#include <QAbstractItemModel>

class AnimationTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AnimationTreeModel(QObject *parent = 0);
    ~AnimationTreeModel() = default;
    
    // Needed for a read only mode
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    int getAnimationStackIndex(AnimationTreeBase *stack) const { return this->playlist.getAnimationStackIndex(stack); }
    std::shared_ptr<AnimationStack> getAnimationStack(unsigned index) const { return this->playlist.getAnimationStack(index); }
    
    bool loadPlaylistFile(QString filePath);
    QString getPlaylistString() const { return this->playlist.getPlaylistString(); }

    // Optional? 
    // QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; 
    
    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

private:
    const AnimationTreeBase *getItem(const QModelIndex &index) const;
    AnimationTreeBase *getItemNonConst(const QModelIndex &index);

    AnimationPlaylist playlist;
};
