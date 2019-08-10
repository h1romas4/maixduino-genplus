#include <bsp.h>
#include <sysctl.h>
#include "maixduino.h"
#include "lcd/lcd.h"
#include "sdcard/sdcard.h"

#include "shared.h"
#include "md_ntsc.h"
#include "sms_ntsc.h"

#define SOUND_FREQUENCY 48000
#define SOUND_SAMPLES_SIZE  2048

#define VIDEO_WIDTH  320
#define VIDEO_HEIGHT 240

md_ntsc_t *md_ntsc;
sms_ntsc_t *sms_ntsc;

static short soundframe[SOUND_SAMPLES_SIZE];

struct _zbank_memory_map zbank_memory_map[256];

int main(void)
{
    k210_begin();
    // wait stable
    msleep(1000);
    printf("hello, maxiduino world.\n");

    // maixduino init
    lcd_begin();
    sdcard_begin();
    fs_begin();

    // system init
    error_init();
    set_config_defaults();

    // video ram init
    sms_ntsc = (sms_ntsc_t *)malloc(sizeof(sms_ntsc_t));
    md_ntsc = (md_ntsc_t *)malloc(sizeof(md_ntsc_t));
    sms_ntsc_init(sms_ntsc, &sms_ntsc_rgb);
    md_ntsc_init(md_ntsc, &md_ntsc_rgb);

    // load rom
    load_rom("COLUMS.BIN");

    // emurator init
    audio_init(SOUND_FREQUENCY, 0);
    system_init();

    lcd_fill_rectangle(100, 100, 200, 200, 0xff00);

    free(md_ntsc);
    free(sms_ntsc);

    printf("maixduino stabled.\n");
    while(1)
        continue;
    return 0;
}
