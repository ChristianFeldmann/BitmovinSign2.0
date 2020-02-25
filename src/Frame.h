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

    // Scale the alpha value for each pixel using this new alpha value. 
    // Very helpful for fading a whole Frame in and out.
    void scaleAlpha(unsigned alphaAdjust);

    std::vector<QColor> data{ std::vector<QColor>(NR_LED_TOTAL) };
};
