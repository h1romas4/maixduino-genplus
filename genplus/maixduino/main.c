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

static uint16_t frame_buffer[320 * 240];
static short soundframe[SOUND_SAMPLES_SIZE];

struct _zbank_memory_map zbank_memory_map[256];

int sdl_input_update(void) {
    return 1;
}

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
    sms_ntsc = calloc(1, sizeof(sms_ntsc_t));
    md_ntsc  = calloc(1, sizeof(md_ntsc_t));
    memset(&bitmap, 0, sizeof(bitmap));
    bitmap.width      = 320;
    bitmap.height     = 240;
    bitmap.pitch      = 320 * 2;
    bitmap.data       = (uint8_t *)frame_buffer;
    bitmap.viewport.changed = 3;

    // load rom
    load_rom("COLUMS.BIN");
    printf("copyright: %s\n", rominfo.copyright);
    printf("romstart: %u\n", rominfo.romstart);
    printf("romend(genplus endian bug): %u\n", rominfo.romend);

    // emurator init
    audio_init(SOUND_FREQUENCY, 0);
    system_init();
    system_reset();

    // init result
    // t_bitmap bitmap;
    // t_snd snd;
    printf("mcycles_vdp: %d\n", mcycles_vdp);
    printf("system_hw: %d\n", system_hw);
    printf("system_bios: %d\n", system_bios);
    printf("system_clock: %d\n", system_clock);
    printf("SVP_cycles: %d\n", SVP_cycles);

    int running = 0;
    int sampling_size;
    // emuration loop
    while(running < 65535) {
        system_frame_gen(0);
        sampling_size = audio_update(soundframe) * 2;
        running++;
    }
    lcd_draw_picture(0, 0, 240, 320, frame_buffer);

    lcd_fill_rectangle(100, 100, 200, 200, 0xff00);

    free(md_ntsc);
    free(sms_ntsc);

    printf("maixduino stabled.\n");
    while(1)
        continue;
    return 0;
}
