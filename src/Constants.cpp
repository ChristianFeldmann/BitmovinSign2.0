#include <Constants.h>

Frame getBlackFrame()
{
    Frame frame;
    frame.reserve(NR_LED_TOTAL);

    for (unsigned i = 0; i < NR_LED_TOTAL; i++)
    {
        frame.push_back(Qt::black);
    }

    return frame;
}

QColor interpolateColors(const QColor &c1, const QColor &c2, double ratio)
{
    int r = std::abs(c2.red() - c1.red()) * ratio + std::min(c1.red(), c2.red());
    int g = std::abs(c2.green() - c1.green()) * ratio + std::min(c1.green(), c2.green());
    int b = std::abs(c2.blue() - c1.blue()) * ratio + std::min(c1.blue(), c2.blue());

    return QColor(r,g,b);
}

unsigned int setRangeOfLedToColor(Frame& frame, unsigned int startIdx, unsigned int nrLed, QColor color)
{
    for (auto i = startIdx; i < startIdx + nrLed; i++)
    {
        frame[i] = color;
    }
    return nrLed;
}