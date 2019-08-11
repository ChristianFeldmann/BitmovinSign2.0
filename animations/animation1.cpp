#include "animation1.h"


void animation1::render_frame(Frame &frame)
{
    this->instagram_color(frame);
}

void animation1::simple_animation(Frame &frame)
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

void animation1::my_animation(Frame &frame)
{
    int count = 0;
    if (this->counter % 3 == 0)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 255, 0, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 255, 0, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 255, 0, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 255, 0, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 255, 0, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 255, 0, 0);

        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 100, 100, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 100, 100, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 100, 100, 255);
    } else if (this->counter % 3 == 1)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 0, 255, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 0, 255, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 0, 255, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 0, 255, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 0, 255, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 0, 255, 0);

        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 100, 100, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 100, 100, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 100, 100, 255);
    } else if (this->counter % 3 == 2)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 0, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 0, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 0, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 0, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 0, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 0, 0, 255);

        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 100, 100, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 100, 100, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 100, 100, 255);
    }
    

    this->counter++;
    if(this->counter > 1000)
    {
        this->counter = 0;
    }
}

void animation1::instagram_color(Frame &frame)
{
    int count = 0;
    if(this->counter % 6 == 0)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 255, 150, 0);
    } else if (this->counter % 6 == 1)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 255, 0, 100);
    } else if (this->counter % 6 == 2)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 255, 0, 100);
    } else if (this->counter % 6 == 3)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 150, 0, 255);
    } else if (this->counter % 6 == 4)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 150, 0, 255);
    } else if (this->counter % 6 == 5)
    {
        this->set_num_of_leds(frame, count, frame.leds_base[0], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[1], 150, 0, 255);
        this->set_num_of_leds(frame, count, frame.leds_base[2], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[3], 255, 0, 100);
        this->set_num_of_leds(frame, count, frame.leds_base[4], 255, 150, 0);
        this->set_num_of_leds(frame, count, frame.leds_base[5], 255, 150, 0);
    }

    if (this->counter % 55 < 11)
    {
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 0, 0, 0);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 0, 0, 0);
        
    } else if (this->counter % 55 < 22)
    {
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 0, 0, 0);
    } else if (this->counter % 55 < 33)
    {
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 0, 150, 255);
    } else if (this->counter % 55 < 44)
    {
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 0, 150, 255);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 0, 150, 255);
    } else if (this->counter % 55 < 55)
    {
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partL.begin(), frame.leds_partL.end(), 0), 0, 0, 0);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partM.begin(), frame.leds_partM.end(), 0), 0, 0, 0);
        this->set_num_of_leds(frame, count, std::accumulate(frame.leds_partR.begin(), frame.leds_partR.end(), 0), 0, 0, 0);
    }

    this->counter++;
    if (this->counter > 10000)
    {
        this->counter = 0;
    }
}

void animation1::set_num_of_leds(Frame &frame, int &start, int num_of_leds, unsigned char red, unsigned char green, unsigned char blue)
{
    for (int i = 0; i < num_of_leds; i++)
    {
        frame.led[start + i].red = red;
        frame.led[start + i].green = green;
        frame.led[start + i].blue = blue;
    }
    start += num_of_leds;
}