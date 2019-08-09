#pragma once

#pragma once
/* The actual output which pushes the data to the sign
 */

#include "../helpers/frame.h"

#include "ws2811.h"

class Output
{
public:
    Output();
    ~Output();

    void pushData(Frame &f) {};

private:
};

