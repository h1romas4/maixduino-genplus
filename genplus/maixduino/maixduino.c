#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "maixduino.h"
#include "lcd/lcd.h"
#include "sdcard/sdcard.h"
#include "sdcard/ff.h"

#define PLL1_OUTPUT_FREQ 400000000UL

uint16_t getValueByRotation(uint8_t rotation);

//
// for Maixduino
//
void k210_begin(void)
{
    // use 8MB memory @see lds/kendryte.ld
    //
    // The AI SRAM memory is only accessible if the following conditions are met:
    //  PLL1 enabled and clock system configuration is correct
    //  KPU not performing neural network calculations
    sysctl_pll_set_freq(SYSCTL_PLL1, PLL1_OUTPUT_FREQ);
    sysctl_clock_enable(SYSCTL_CLOCK_AI);
}

//
// for Maixduino (SPI0)
//
void lcd_begin(void)
{
    fpioa_set_function(SIPEED_ST7789_SS_PIN  , (fpioa_function_t)(FUNC_SPI0_SS0 + SIPEED_ST7789_SS));
    fpioa_set_function(SIPEED_ST7789_SCLK_PIN, (fpioa_function_t)FUNC_SPI0_SCLK);
    sysctl_set_spi0_dvp_data(1);
    lcd_init(0, SIPEED_ST7789_SS, SIPEED_ST7789_RST_GPIONUM, SIPEED_ST7789_DCX_GPIONUM, 15000000, SIPEED_ST7789_RST_PIN,  SIPEED_ST7789_DCX_PIN, 3);
    lcd_set_direction(getValueByRotation(0));
    lcd_clear(0x0000);
}

//
// for Maixduino (SPI1)
//
uint8_t sdcard_begin(void)
{
    // Maixduino SPI SD Card
    //  SPIClass(spi_id_t spi_bus, int8_t sck, int8_t miso, int8_t mosi, int8_t ss, uint32_t freq = 1000000);
    //  SPIClass spi1(SPI1, 27, 26, 28, 29);
    //  Sd2Card card(spi1);
    fpioa_set_function(27, FUNC_SPI1_SCLK);
    fpioa_set_function(28, FUNC_SPI1_D0);
    fpioa_set_function(26, FUNC_SPI1_D1);
    fpioa_set_function(29, FUNC_SPI1_SS3);

    printf("sdcard init start.\n");

    uint8_t status;
    status = sd_init();
    printf("sd init %d\n", status);
    if (status != 0) {
        return status;
    }

    printf("card info status %d\n", status);
    printf("CardCapacity:%ld\n", cardinfo.CardCapacity);
    printf("CardBlockSize:%d\n", cardinfo.CardBlockSize);
    return 0;
}

uint8_t fs_begin(void)
{
    static FATFS sdcard_fs;
    FRESULT status;
    DIR dj;
    FILINFO fno;

    printf("sdcard fs init start.\n");
    status = f_mount(&sdcard_fs, _T("0:"), 1);
    printf("mount sdcard:%d\n", status);
    if (status != FR_OK)
        return status;

    printf("printf filename\n");
    status = f_findfirst(&dj, &fno, _T("0:"), _T("*"));
    while (status == FR_OK && fno.fname[0]) {
        if (fno.fattrib & AM_DIR)
            printf("dir:%s\n", fno.fname);
        else
            printf("file:%s\n", fno.fname);
        status = f_findnext(&dj, &fno);
    }
    f_closedir(&dj);
    return 0;
}

uint16_t getValueByRotation(uint8_t rotation)
{
    uint16_t v = DIR_YX_RLDU;
    switch(rotation) {
        case 0:
            v = DIR_YX_RLDU;
            break;
        case 1:
            v = DIR_XY_RLUD;
            break;
        case 2:
            v = DIR_YX_LRUD;
            break;
        case 3:
            v = DIR_XY_LRDU;
            break;
    }
    return v;
}
