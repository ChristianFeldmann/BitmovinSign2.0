#pragma once

#include "animationInterface.h"
#include "../helpers/frame.h"

class animation1: public animationInterface
{
private:
    /* data */
    int counter {0};
    void simple_animation(Frame &frame);
    void my_animation(Frame &frame);
    void instagram_color(Frame &frame);
    void set_num_of_leds(Frame &frame, int &start, int num_of_leds, unsigned char red, unsigned char green, unsigned char blue);

public:
    void render_frame(Frame &frame) override;
};

