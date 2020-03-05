#include "GeneralSettings.h"

GeneralSettings::GeneralSettings(AnimationTreeBase *rootPlaylist) 
  : AnimationTreeBase(rootPlaylist)
{
    this->addParameter("Transition Time", &this->animationTransitionTime);
}

QVariant GeneralSettings::data(int column) const
{
    if (column == 0)
    {
        return QVariant("General Settings");
    }

    return {};
}

bool GeneralSettings::savePlaylist(QDomElement &root) const
{
    QDomElement d = root.ownerDocument().createElement("GeneralSettings");
    bool success = saveParameters(d);
    root.appendChild(d);
    return success;
}

bool GeneralSettings::loadProperties(QDomElement &root)
{
    return false;
}