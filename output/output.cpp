
#include "output.h"

#include <QDebug>

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)
#define LED_COUNT               489

Output::Output()
{
    ledstring.freq = TARGET_FREQ;
    ledstring.dmanum = DMA;
    ledstring.channel[0].gpionum = GPIO_PIN;
    ledstring.channel[0].count = LED_COUNT;
    ledstring.channel[0].invert = 0;
    ledstring.channel[0].brightness = 255;
    ledstring.channel[0].strip_type = STRIP_TYPE;
    ledstring.channel[1].gpionum = 0;
    ledstring.channel[1].count = 0;
    ledstring.channel[1].invert = 0;
    ledstring.channel[1].brightness = 0;

    ws2811_return_t ret;
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        qDebug() << "ws2811_init failed: " << ws2811_get_return_t_str(ret);
    }
    
    qDebug() << "Rendering...";
    memset(ledstring.channel[0].leds, 0, sizeof(ws2811_led_t) * LED_COUNT);
    int i = 0;
    ledstring.channel[0].leds[i=i+0]=255;
    
    ledstring.channel[0].leds[i=i+34]=255;
    ledstring.channel[0].leds[i=i+36]=255;
    ledstring.channel[0].leds[i=i+33]=255;
    ledstring.channel[0].leds[i=i+34]=255;
    ledstring.channel[0].leds[i=i+35]=255;
    ledstring.channel[0].leds[i=i+34]=255;
    
    ledstring.channel[0].leds[i=i+14]=255;
    ledstring.channel[0].leds[i=i+14]=255;
    ledstring.channel[0].leds[i=i+2]=255;
    ledstring.channel[0].leds[i=i+7]=255;
    ledstring.channel[0].leds[i=i+7]=255;
    ledstring.channel[0].leds[i=i+2]=255;
    
    ledstring.channel[0].leds[i=i+26]=255;
    ledstring.channel[0].leds[i=i+26]=255;
    ledstring.channel[0].leds[i=i+5]=255;
    ledstring.channel[0].leds[i=i+14]=255;
    ledstring.channel[0].leds[i=i+14]=255;
    ledstring.channel[0].leds[i=i+5]=255;
    
    ledstring.channel[0].leds[i=i+42]=255;
    ledstring.channel[0].leds[i=i+41]=255;
    ledstring.channel[0].leds[i=i+8]=255;
    ledstring.channel[0].leds[i=i+24]=255;
    ledstring.channel[0].leds[i=i+24]=255;
    ledstring.channel[0].leds[i=i+8]=255;
    qDebug() << "i: " << i;
    ret = ws2811_render(&ledstring);
    if (ret != WS2811_SUCCESS)
    {
        qDebug() << "render failed: " << ws2811_get_return_t_str(ret);
    }
}

