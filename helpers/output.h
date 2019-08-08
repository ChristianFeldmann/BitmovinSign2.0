#pragma once

/* The actual output which pushes the data to the sign
 */

#include "frame.h"

class signOutput
{
public:
    signOutput();
    ~signOutput();

    void pushData(Frame &f) {};

private:
};

