#include "AnimationPlaylist.h"

#include <QBuffer>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

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
    QByteArray fileBytes = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<playlistItems version=\"2.0\">\n"
                           " <playlist>\n"
                           "  <stack>\n"
                           "   <HighlightRotation>\n"
                           "    <Float Name=\"speedBackground\">0.1</Float>\n"
                           "    <Color Name=\"color Background\">#1ebeb1</Color>\n"
                           "    <UInt Name=\"stripes Background\">9</UInt>\n"
                           "    <Float Name=\"length Background\">5</Float>\n"
                           "    <Float Name=\"speedLeft\">0.1</Float>\n"
                           "    <Color Name=\"color Left\">#1ebeb1</Color>\n"
                           "    <UInt Name=\"stripes Left\">2</UInt>\n"
                           "    <Float Name=\"length Left\">5</Float>\n"
                           "    <Float Name=\"speedMiddle\">0.1</Float>\n"
                           "    <Color Name=\"color Middle\">#1ebeb1</Color>\n"
                           "    <UInt Name=\"stripes Middle\">5</UInt>\n"
                           "    <Float Name=\"length Middle\">5</Float>\n"
                           "    <Float Name=\"speedRight\">0.1</Float>\n"
                           "    <Color Name=\"color Right\">#1ebeb1</Color>\n"
                           "    <UInt Name=\"stripes Right\">7</UInt>\n"
                           "    <Float Name=\"length Right\">5</Float>\n"
                           "   </HighlightRotation>\n"
                           "  </stack>\n"
                           "  <stack>\n"
                           "   <ConstantColor>\n"
                           "    <Color Name=\"color\">#157da3</Color>\n"
                           "   </ConstantColor>\n"
                           "   <HighlightSparkling>\n"
                           "    <Color Name=\"color\">#ffffff</Color>\n"
                           "    <Float Name=\"speed\">1</Float>\n"
                           "    <Float Name=\"rate\">20</Float>\n"
                           "   </HighlightSparkling>\n"
                           "  </stack>\n"
                           "  <stack>\n"
                           "   <ConstantColor>\n"
                           "    <Color Name=\"color\">#bb3720</Color>\n"
                           "   </ConstantColor>\n"
                           "   <Alarm>\n"
                           "    <Float Name=\"speed\">1</Float>\n"
                           "    <Color Name=\"color\">#000000</Color>\n"
                           "    <Float Name=\"span\">30</Float>\n"
                           "   </Alarm>\n"
                           "   <Alarm>\n"
                           "    <Float Name=\"speed\">-1</Float>\n"
                           "    <Color Name=\"color\">#000000</Color>\n"
                           "    <Float Name=\"span\">40</Float>\n"
                           "   </Alarm>\n"
                           "  </stack>\n"
                           "  <stack>\n"
                           "   <SegmentsFlashing>\n"
                           "    <Float Name=\"speed\">0.5</Float>\n"
                           "    <Color Name=\"color\">#1eabe2</Color>\n"
                           "    <Int Name=\"timeOffsetBetweenSegments\">50</Int>\n"
                           "    <Int Name=\"timeToWaitFullColor\">50</Int>\n"
                           "   </SegmentsFlashing>\n"
                           "  </stack>\n"
                           " </playlist>\n"
                           "</playlistItems>\n"
                           "";
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
    if (number >= 0 && number < this->animationStackList.size())
    {
        return this->animationStackList.at(number).get();
    }
    return nullptr;
}

size_t AnimationPlaylist::childCount() const 
{ 
    return this->animationStackList.size(); 
}

int AnimationPlaylist::childNumber(AnimationTreeBase *child) const
{
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

    // Iterate over all items in the playlist
    QDomNode n = root.firstChild();
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