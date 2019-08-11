
#include "Output.h"

#include <QDebug>

#define LED_COUNT 489

Output::Output()
{
#ifdef __arm__
    ledstring.freq = WS2811_TARGET_FREQ;
    ledstring.dmanum = 10;
    ledstring.render_wait_time = 0;
    ledstring.channel[0].gpionum = 18;
    ledstring.channel[0].count = LED_COUNT;
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
    for (int i = 0; i < 489; i++)
    {
        ws2811_led_t v = 0;
        v += ((f[i].green()) << 16);
        v += ((f[i].red()) << 8);
        v += (f[i].blue());

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
