#pragma once

#include <vector>
#include <QColor>
#include <QDomElement>
#include <QImage>
#include <QPointF>
#include <QSize>

#include <cstdlib>
#include <climits>
#include <map>
#include <memory>

#include <algorithm>

class AnimationInterface;

const unsigned NR_LED_TOTAL = 489;
const unsigned NR_LED_BACKGROUND = 206;
const unsigned NR_LED_PART_LEFT = 46;
const unsigned NR_LED_PART_MIDDLE = 90;
const unsigned NR_LED_PART_RIGHT = 147;

const unsigned OFFSET_PART_LEFT = NR_LED_BACKGROUND;
const unsigned OFFSET_PART_MIDDLE = OFFSET_PART_LEFT + NR_LED_PART_LEFT;
const unsigned OFFSET_PART_RIGHT = OFFSET_PART_MIDDLE + NR_LED_PART_MIDDLE;

const std::vector<unsigned> LED_PARTS_BACKGROUND = {34, 36, 33, 34, 35, 34};
const std::vector<unsigned> LED_PARTS_PART_LEFT = {14, 14, 2, 7, 7, 2};
const std::vector<unsigned> LED_PARTS_PART_MIDDLE = {26, 26, 5, 14, 14, 5};
const std::vector<unsigned> LED_PARTS_PART_RIGHT = {42, 41, 8, 24, 24, 8};

const std::vector<QPointF> POINTS_BASE = {QPointF{0.5, 0.98}, QPointF{0.03 , 0.75}, QPointF{0.03 , 0.27}, QPointF{0.5, 0.03}, QPointF{0.97, 0.27}, QPointF{0.97, 0.75}};
const std::vector<QPointF> POINTS_PART_L = {QPointF{0.09, 0.38}, QPointF{0.29, 0.5}, QPointF{0.09, 0.64}, QPointF{0.09, 0.56}, QPointF{0.17 , 0.5}, QPointF{0.09 , 0.45}};
const std::vector<QPointF> POINTS_PART_M = {QPointF{0.21, 0.27}, QPointF{0.58, 0.50}, QPointF{0.21, 0.74}, QPointF{0.21, 0.61}, QPointF{0.39 , 0.5}, QPointF{0.21 , 0.40}};
const std::vector<QPointF> POINTS_PART_R = {QPointF{0.37, 0.16}, QPointF{0.93, 0.50}, QPointF{0.37, 0.85}, QPointF{0.37, 0.69}, QPointF{0.67, 0.5}, QPointF{0.37 , 0.32}};

const std::vector<unsigned> NR_LED_LIST = {NR_LED_BACKGROUND, NR_LED_PART_LEFT, NR_LED_PART_MIDDLE, NR_LED_PART_RIGHT};

const std::vector<unsigned> OFFSET_LIST = {0, OFFSET_PART_LEFT, OFFSET_PART_MIDDLE, OFFSET_PART_RIGHT};

const QColor BITMOVIN_BLUE = QColor(30, 171, 226);

const unsigned MAX_RECENT_FILES = 10;

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}

const unsigned imageWidth = 120;
const unsigned imageHeight = 120;
const QSize imageSize = QSize(imageWidth, imageHeight);

class Frame;
struct RenderMemory
{
    std::map<int, Frame> frameMap;
    std::map<int, QImage> imageMap;
};

// Identical to a QDomElement, but we add some convenience functions (findChildValue and appendProperiteChild)
// for putting values into the playlist and reading them from the playlist.
typedef QPair<QString, QString> QStringPair;
typedef QList<QStringPair> QStringPairList;
class QDomElementSign : public QDomElement
{
public:
    // Copy constructor so we can initialize from a QDomElement
    QDomElementSign(const QDomElement &a) : QDomElement(a) {}
    // Look through all the child items. If one child element exists with the given tagName, return it's text node.
    // All attributes of the child (if found) are appended to attributes.
    QString findChildValue(const QString &tagName) const { QStringPairList b; return findChildValue(tagName, b); }
    QString findChildValue(const QString &tagName, QStringPairList &attributeList) const;
    // Some convenient find functions that do casting and can return a default value if the key was not found
    int findChildValueInt(const QString &tagName, int defaultValue) const { QString r = findChildValue(tagName); return r.isEmpty() ? defaultValue : r.toInt(); };
    double findChildValueDouble(const QString &tagName, double defaultValue) const { QString r = findChildValue(tagName); return r.isEmpty() ? defaultValue : r.toDouble(); };
    // Append a new child to this element with the given type, and name (as text node).
    // All QString pairs in ValuePairList are appended as attributes.
    void appendProperiteChild(const QString &type, const QString &name, const QStringPairList &attributes = QStringPairList())
    {
        QDomElement newChild = ownerDocument().createElement(type);
        newChild.appendChild(ownerDocument().createTextNode(name));
        for (int i = 0; i < attributes.length(); i++)
            newChild.setAttribute(attributes[i].first, attributes[i].second);
        appendChild(newChild);
    }
};
