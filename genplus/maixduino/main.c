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

    int running = true;
    int sampling_size;
    // emuration loop
    while(running) {
        system_frame_gen(0);
        sampling_size = audio_update(soundframe) * 2;
        lcd_set_area(0, 0, 320 - 1, 240 - 1);
        tft_write_half(frame_buffer, 320 * 240);
    }

    printf("maixduino stabled.\n");
    while(1)
        continue;
    return 0;
}
