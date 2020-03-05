#pragma once

#include <memory>
#include <QVariant>
#include <QDomElement>

#include "Parameter.h"

/* This base adds the ability for a hierarchical structure where
 * each item in the tree knows his parents and can have children.
 *
 * This is mostly useful for the QAbstractTreeModel which we use to
 * represent and edit the playlist.
 */
class AnimationTreeBase
{
public:
    AnimationTreeBase() = delete;
    AnimationTreeBase(AnimationTreeBase *parent) { this->parent = parent; }
    ~AnimationTreeBase() = default;

    virtual AnimationTreeBase *child(int number) const = 0;
    virtual size_t childCount() const = 0;
    virtual int childNumber(AnimationTreeBase *child) const = 0;
    virtual QVariant data(int column) const = 0;

    virtual bool removeChildren(int pos, int rows) = 0;

    AnimationTreeBase *getParent() const { return this->parent; }

    virtual bool savePlaylist(QDomElement &root) const = 0;
    virtual bool canDropItem(QDomElement &root) const;

    virtual QString getWidgetName() const { return "AnimationTreeBase"; }

    void addParameter(QString name, QColor *color);
    void addParameter(QString name, int *value);
    void addParameter(QString name, unsigned *value);
    void addParameter(QString name, float *value);
    void addParameter(QString name, int *enumInteger, QStringList enumValues);
    virtual QList<QPointer<Parameter>> getParameters() { return this->parameters; }
    bool saveParameters(QDomElement &plist) const;
    bool loadParameters(QDomElement &plist);

    int propertiesWidgetIndex {-1};

protected:
    AnimationTreeBase *parent{ nullptr };

    QWidget *propertiesWidget{ nullptr };

    enum class ItemType
    {
        Playlist,
        Stack,
        Animation,
        GeneralSettings
    };
    virtual ItemType getItemType() const = 0;

    QList<QPointer<Parameter>> parameters;
};