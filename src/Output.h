#pragma once
/* The actual output which pushes the data to the sign
 */

#include "Constants.h"
#include "Frame.h"

#ifdef __arm__
#include <ws2811/ws2811.h>
#endif

class Output
{
public:
    Output();
    ~Output();

    void pushData(Frame &f);

private:
#ifdef __arm__
    ws2811_t ledstring;
#endif

    bool initialized{false};
};
