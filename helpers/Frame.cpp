#include "Frame.h"

#include <algorithm>

LedColor LedColor::black = LedColor();
LedColor LedColor::white = LedColor(255, 255, 255);
LedColor LedColor::bitmovinBlue = LedColor(30, 171, 226);

LedColor LedColor::interpolateColors(LedColor &c1, LedColor &c2, double ratio)
{
    LedColor newColor;
    int r = int((double(c2.red) - double(c1.red)) * ratio + double(c1.red));
    int g = int((double(c2.green) - double(c1.green)) * ratio + double(c1.green));
    int b = int((double(c2.blue) - double(c1.blue)) * ratio + double(c1.blue));
    newColor.red = (r < 0) ? 0 : (r > 255) ? 255 : r;
    newColor.green = (g < 0) ? 0 : (g > 255) ? 255 : g;
    newColor.blue = (b < 0) ? 0 : (b > 255) ? 255 : b;
    return newColor;
}

Frame::Frame()
{
    ledData = std::vector<LedColor>(NR_LED_TOTAL);
};

unsigned int Frame::setRangeOfLedToColor(unsigned int startIdx, unsigned int nrLed, LedColor color)
{
    for (auto i = startIdx; i < startIdx + nrLed; i++)
    {
        this->ledData[i] = color;
    }
    return nrLed;
}