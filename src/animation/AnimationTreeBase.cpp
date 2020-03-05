#include "AnimationTreeBase.h"

#include <cassert>
#include <QDebug>

bool AnimationTreeBase::canDropItem(QDomElement &root) const
{
    QString tagName = root.tagName().toLower();
    const auto itemType = this->getItemType();
    if ((tagName == "stack" && itemType == ItemType::Playlist) || (tagName != "stack" && itemType == ItemType::Stack))
    {
        return true;
    }
    return false;
}

void AnimationTreeBase::addParameter(QString name, QColor *color)
{
    this->parameters.push_back(new Parameter(name, color));
}

void AnimationTreeBase::addParameter(QString name, int *value)
{
    this->parameters.push_back(new Parameter(name, value));
}

void AnimationTreeBase::addParameter(QString name, unsigned *value)
{
    this->parameters.push_back(new Parameter(name, value));
}

void AnimationTreeBase::addParameter(QString name, float *value)
{
    this->parameters.push_back(new Parameter(name, value));
}

void AnimationTreeBase::addParameter(QString name, int *enumInteger, QStringList enumValues)
{
    this->parameters.push_back(new Parameter(name, enumInteger, enumValues));
}

bool AnimationTreeBase::saveParameters(QDomElement &root) const
{
    bool success = true;
    for (auto &parameter : this->parameters)
    {
        success &= parameter->appendProperty(root);
    }
    return success;
}

bool AnimationTreeBase::loadParameters(QDomElement &root)
{
    QDomNodeList children = root.childNodes();
    bool success = true;
    for (int i = 0; i < children.length(); i++)
    {
        QDomElement childElem = children.item(i).toElement();
        QString paramName = childElem.attribute("Name");
        if (paramName.isEmpty())
        {
            return false;
        }
        
        bool paramFound = false;
        for (auto param : this->parameters)
        {
            if (param->name == paramName)
            {
                success &= param->loadFromElement(childElem);
                paramFound = true;
                break;
            }
        }
        if (!paramFound)
        {
            qDebug() << "Unable to find parameter " << paramName;
            success = false;
        }
    }

    return success;
}
