#include "animation1.h"


void animation1::render_frame(Frame &frame)
{
    for (int i = 0; i < TOTAL_LEDS; i++)
    {
        if (this->counter == i)
        {
            frame.led[i].red = 255;
            frame.led[i].green = 0;
            frame.led[i].blue = 0;
        }
        else
        {
            frame.led[i].red = 0;
            frame.led[i].green = 0;
            frame.led[i].blue = 0;
        }
    }

    this->counter++;
    if (this->counter > 489)
    {
        this->counter = 0;
    }
}