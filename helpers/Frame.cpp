#include "Frame.h"

LedColor LedColor::black = LedColor();
LedColor LedColor::white = LedColor(255, 255, 255);
LedColor LedColor::bitmovinBlue = LedColor(30, 171, 226);

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
