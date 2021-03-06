
#include "Output.h"

#ifdef __arm__
#include <QDebug>
#include <algorithm>
#endif

Output::Output()
{
#ifdef __arm__
    ledstring.freq = WS2811_TARGET_FREQ;
    ledstring.dmanum = 10;
    ledstring.render_wait_time = 0;
    ledstring.channel[0].gamma = nullptr;
    ledstring.channel[0].gpionum = 18;
    ledstring.channel[0].count = NR_LED_TOTAL;
    ledstring.channel[0].invert = 0;
    ledstring.channel[0].brightness = 255;
    ledstring.channel[0].strip_type = WS2811_STRIP_RGB;
    ledstring.channel[1].gpionum = 0;
    ledstring.channel[1].count = 0;
    ledstring.channel[1].invert = 0;
    ledstring.channel[1].brightness = 0;

    ws2811_return_t ret = ws2811_init(&this->ledstring);
    if (ret != WS2811_SUCCESS)
    {
        qDebug() << "ws2811_init failed: " << ws2811_get_return_t_str(ret);
        return;
    }
#endif

    initialized = true;
}

Output::~Output()
{
#ifdef __arm__
    ws2811_fini(&this->ledstring);
#endif
}

void Output::pushData(Frame &f)
{
    if (!initialized)
        return;
    // qDebug() << "Rendering...";
#ifdef __arm__
    
    // Convert from frame data to ws2811 data format
    for (int i = 0; i < NR_LED_TOTAL; i++)
    {
        ws2811_led_t v = 0;
        
        int r = clip((f.data[i].red() * f.data[i].alpha() / 255), 0, 255);
        int g = clip((f.data[i].green() * f.data[i].alpha() / 255), 0, 255);
        int b = clip((f.data[i].blue() * f.data[i].alpha() / 255), 0, 255);
        
        v += (g << 16);
        v += (r << 8);
        v += b;

        ledstring.channel[0].leds[i] = v;
    }
    
    ws2811_return_t ret = ws2811_render(&ledstring);
    if (ret != WS2811_SUCCESS)
    {
        qDebug() << "render failed: " << ws2811_get_return_t_str(ret);
    }
#else
    Q_UNUSED(f);
#endif
}
