#pragma once

#include <QColor>
#include <vector>

#include "Constants.h"

class Frame
{
public:
    Frame() = default;
    ~Frame() = default;

    void clearFrame();
    unsigned setRangeToColor(unsigned startIdx, unsigned count, QColor color);

    // Blend the other fram on top of this frame. The reuslt is saved in this frame.
    void blendWithFrame(Frame &other);

    std::vector<QColor> data{ std::vector<QColor>(NR_LED_TOTAL) };
};
