
#include "output.h"

#include <QDebug>

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
#define STRIP_TYPE              WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)
#define LED_COUNT               489

Output::Output()
{
    ws2811_t ledstring;
    ledstring.freq = TARGET_FREQ;
    ledstring.dmanum = DMA;
    ledstring.render_wait_time = 0;
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
    for (int i=0; i<LED_COUNT; i++)
    {
        ledstring.channel[0].leds[i] = 0x00ffffff;
    }
    int i = 0;
    ledstring.channel[0].leds[i=i+0]=0x00ffffff;
    ledstring.channel[0].leds[i+1]=0x0000ffff;
    ledstring.channel[0].leds[i+2]=0x00ff00ff;
    ledstring.channel[0].leds[i+3]=0x00ffff00;
    
    ledstring.channel[0].leds[i=i+34]=0x00ff00ff;
    ledstring.channel[0].leds[i=i+36]=0x00ff00ff;
    ledstring.channel[0].leds[i=i+33]=0x00ff00ff;
    ledstring.channel[0].leds[i=i+34]=0x00ff00ff;
    ledstring.channel[0].leds[i=i+35]=0x00ff00ff;
    ledstring.channel[0].leds[i=i+34]=0x00ff00ff;
    
    ledstring.channel[0].leds[i=i+14]=0x00ffff00;
    ledstring.channel[0].leds[i=i+14]=0x00ffff00;
    ledstring.channel[0].leds[i=i+2]=0x00ffff00;
    ledstring.channel[0].leds[i=i+7]=0x00ffff00;
    ledstring.channel[0].leds[i=i+7]=0x00ffff00;
    ledstring.channel[0].leds[i=i+2]=0x00ffff00;
    
    ledstring.channel[0].leds[i=i+26]=0x0000ffff;
    ledstring.channel[0].leds[i=i+26]=0x0000ffff;
    ledstring.channel[0].leds[i=i+5]=0x0000ffff;
    ledstring.channel[0].leds[i=i+14]=0x0000ffff;
    ledstring.channel[0].leds[i=i+14]=0x0000ffff;
    ledstring.channel[0].leds[i=i+5]=0x0000ffff;
    
    ledstring.channel[0].leds[i=i+42]=0x00ff0000;
    ledstring.channel[0].leds[i=i+41]=0x00ff0000;
    ledstring.channel[0].leds[i=i+8]=0x00ff0000;
    ledstring.channel[0].leds[i=i+24]=0x00ff0000;
    ledstring.channel[0].leds[i=i+24]=0x00ff0000;
    ledstring.channel[0].leds[i=i+8]=0x00ff0000;
    //qDebug() << "i: " << i;
    ret = ws2811_render(&ledstring);
    if (ret != WS2811_SUCCESS)
    {
        qDebug() << "render failed: " << ws2811_get_return_t_str(ret);
    }
    
    qDebug() << "Rendering done ";
}

