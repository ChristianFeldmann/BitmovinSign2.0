#include "AnimationPlaylist.h"

#include <QBuffer>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

AnimationPlaylist::AnimationPlaylist() : AnimationTreeBase(nullptr)
{
    this->generalSettings = std::make_shared<GeneralSettings>(this);
}

bool AnimationPlaylist::loadPlaylistFile(QString filename)
{
    QFile file(filename);
    QFileInfo fileInfo(file);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    // Load the playlist file to buffer
    QByteArray fileBytes = file.readAll();
    return this->loadPlaylistFromByteArray(fileBytes);

    return true;
}

QString AnimationPlaylist::getPlaylistString() const
{
    // Create the XML document structure
    QDomDocument document;
    document.appendChild(document.createProcessingInstruction(QStringLiteral("xml"), QStringLiteral("version=\"1.0\" encoding=\"UTF-8\"")));
    QDomElement plist = document.createElement(QStringLiteral("playlistItems"));
    plist.setAttribute(QStringLiteral("version"), QStringLiteral("2.0"));
    document.appendChild(plist);
    this->savePlaylist(plist);
    return document.toString();
}

bool AnimationPlaylist::createDefaultPlaylist()
{
    QFile file(":/Default.signPlaylist");
    file.open(QIODevice::ReadOnly);
    QByteArray fileBytes = file.readAll();
    return this->loadPlaylistFromByteArray(fileBytes);
}

std::shared_ptr<AnimationStack> AnimationPlaylist::getAnimationStack(unsigned idx) const
{
    if (idx >= this->animationStackList.size())
    {
        return nullptr;
    }
    return this->animationStackList[idx];
}

int AnimationPlaylist::getAnimationStackIndex(AnimationTreeBase *stack) const
{
    for (size_t i = 0; i < this->animationStackList.size(); i++)
    {
        if (this->animationStackList[i].get() == stack)
        {
            return int(i);
        }
    }
    return -1;
}

bool AnimationPlaylist::insertStack(int pos)
{
    if (pos < 0 || pos > int(this->animationStackList.size()))
        return false;

    auto newStack = std::make_shared<AnimationStack>(this);
    this->animationStackList.insert(this->animationStackList.begin() + pos, newStack);

    return true;
}

AnimationTreeBase *AnimationPlaylist::child(int number) const
{
    if (number == 0)
    {
        return generalSettings.get();
    }
    if (number >= 0 && number < this->animationStackList.size())
    {
        return this->animationStackList.at(number).get();
    }
    return nullptr;
}

size_t AnimationPlaylist::childCount() const
{ 
    return this->animationStackList.size() + 1;
}

int AnimationPlaylist::childNumber(AnimationTreeBase *child) const
{
    if (child == this->generalSettings.get())
    {
        return 0;
    }
    for (size_t i = 0; i < this->animationStackList.size(); i++)
    {
        if (this->animationStackList[i].get() == child)
        {
            return int(i);
        }
    }
    return 0;
}

QVariant AnimationPlaylist::data(int column) const
{
    Q_UNUSED(column);
    return {};
}

bool AnimationPlaylist::removeChildren(int pos, int count)
{
    if (pos == 0)
    {
        return false;
    }
    if (pos < 0 || pos > int(this->animationStackList.size()))
    {
        return false;
    }

    this->animationStackList.erase(this->animationStackList.begin() + pos, this->animationStackList.begin() + pos + count);
    return true;
}

bool AnimationPlaylist::savePlaylist(QDomElement &root) const
{
    QDomElement d = root.ownerDocument().createElement("playlist");
    bool success = true;
    for (auto &stack : this->animationStackList)
    {
        success &= stack->savePlaylist(d);
    }
    root.appendChild(d);
    return success;
}

bool AnimationPlaylist::loadPlaylistFromByteArray(QByteArray data)
{
    QBuffer buffer(&data);

    // Try to open the DOM document
    QDomDocument doc;
    QString errorMessage;
    int errorLine;
    int errorColumn;
    bool success = doc.setContent(&buffer, false, &errorMessage, &errorLine, &errorColumn);
    if (!success)
    {
        qDebug() << "Error loading playlist - The playlist file format could not be recognized.";
        return false;
    }

    // Get the root and parser the header
    QDomElement root = doc.documentElement();
    QString tmp1 = root.tagName();
    QString tmp2 = root.attribute("version");
    if (root.tagName() != "playlistItems" || root.attribute("version") != "2.0")
    {
        qDebug() << "Error loading playlist - The playlist file format could not be recognized.";
        return false;
    }

    QDomNode playlistNode = root.firstChild();
    if (!playlistNode.isElement())
    {
        qDebug() << "Error loading playlist - The 'playlist' node could not be found.";
        return false;
    }

    QDomElement playlistElement = playlistNode.toElement();
    if (playlistElement.tagName() == "general")
    {
        
    }

    if (playlistElement.tagName() != "playlist")
    {
        qDebug() << "Error loading playlist - The 'playlist' node could not be found.";
        return false;
    }

    QDomNode n = playlistElement.firstChild();
    while (!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement elem = n.toElement();
            this->addStackFromDomElement(elem);
        }
        n = n.nextSibling();
    }

    return true;
}

void AnimationPlaylist::addStackFromDomElement(QDomElement &elem, int position)
{
    auto newStack = std::make_shared<AnimationStack>(this, elem);
    if (position >= 0)
    {
        auto it = this->animationStackList.begin();
        this->animationStackList.insert(it + position, newStack);
    }
    else
    {
        this->animationStackList.push_back(newStack);
    }
}