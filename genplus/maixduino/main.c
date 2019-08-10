#include <bsp.h>
#include <sysctl.h>
#include "maixduino.h"
#include "lcd/lcd.h"
#include "sdcard/sdcard.h"

#include "shared.h"
#include "md_ntsc.h"
#include "sms_ntsc.h"

md_ntsc_t *md_ntsc;
sms_ntsc_t *sms_ntsc;

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

    // init
    error_init();
    set_config_defaults();

    load_rom("COLUMS.BIN");
    system_init();

    lcd_fill_rectangle(100, 100, 200, 200, 0xff00);

    printf("maixduino stabled.\n");
    while(1)
        continue;
    return 0;
}
