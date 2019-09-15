#pragma once

#include "Frame.h"

#include <QImage>

#include <map>

struct RenderMemory
{
    std::map<unsigned, Frame> frameMap;
    std::map<unsigned, QImage> imageMap;
    std::map<unsigned, bool> imageUsed;     ///< did the animation render to the image? 

    // In the threads, we also perform the rendering of the result into an image
    // for faster drawing
    std::map<unsigned, QImage> debuggerImageMap;

    // The result of the render
    Frame outputFrame;
    QImage debuggerOutputFrame;
};
