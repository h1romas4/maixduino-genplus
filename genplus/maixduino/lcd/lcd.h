/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>
#include "st7789.h"

#ifdef __cplusplus
extern "C" {
#endif


/* clang-format off */
#define LCD_X_MAX   (240)
#define LCD_Y_MAX   (320)
#define LCD_MAX_PIXELS (76800) //LCD_X_MAX*LCD_Y_MAX

#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F
#define USER_COLOR  0xAA55
/* clang-format on */

typedef enum _lcd_dir
{
    DIR_XY_RLUD = 0x00,
    DIR_YX_RLUD = 0x20,
    DIR_XY_LRUD = 0x40,
    DIR_YX_LRUD = 0x60,
    DIR_XY_RLDU = 0x80,
    DIR_YX_RLDU = 0xA0,
    DIR_XY_LRDU = 0xC0,
    DIR_YX_LRDU = 0xE0,
    DIR_XY_MASK = 0x20,
    DIR_RL_MASK = 0x40,
    DIR_UD_MASK = 0x80
} lcd_dir_t;

typedef struct _lcd_ctl
{
    uint8_t mode;
    uint8_t dir;
    uint16_t width;
    uint16_t height;
} lcd_ctl_t;

void lcd_polling_enable(void);
void lcd_interrupt_enable(void);
void lcd_init(uint8_t spi, uint8_t ss, uint8_t rst, uint8_t dcx, uint32_t freq, int8_t rst_pin, int8_t dcx_pin, uint8_t dma_ch);
void lcd_clear(uint16_t color);
void lcd_set_freq(uint32_t freq);
uint32_t lcd_get_freq();
void lcd_set_direction(lcd_dir_t dir);
void lcd_set_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_draw_string(uint16_t x, uint16_t y, char *str, uint16_t color);
void lcd_draw_picture(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint16_t *ptr);
void lcd_draw_pic_roi(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t rx, uint16_t ry, uint16_t rw, uint16_t rh, uint32_t *ptr);
void lcd_draw_pic_gray(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint8_t *ptr);
void lcd_draw_pic_grayroi(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t rx, uint16_t ry, uint16_t rw, uint16_t rh, uint8_t *ptr);
void lcd_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t width, uint16_t color);
void lcd_ram_cpyimg(char* lcd, int lcdw, char* img, int imgw, int imgh, int x, int y);

void lcd_begin(void);
uint16_t getValueByRotation(uint8_t rotation);

#define SIPEED_ST7789_RST_PIN    37
#define SIPEED_ST7789_DCX_PIN    38
#define SIPEED_ST7789_SS_PIN     36
#define SIPEED_ST7789_SCLK_PIN   39

// default peripheral
#define SIPEED_ST7789_RST_GPIONUM  6
#define SIPEED_ST7789_DCX_GPIONUM  7
#define SIPEED_ST7789_SS           3

#define COLOR_BLACK       0x0000
#define COLOR_NAVY        0x000F
#define COLOR_DARKGREEN   0x03E0
#define COLOR_DARKCYAN    0x03EF
#define COLOR_MAROON      0x7800
#define COLOR_PURPLE      0x780F
#define COLOR_OLIVE       0x7BE0
#define COLOR_LIGHTGREY   0xC618
#define COLOR_DARKGREY    0x7BEF
#define COLOR_BLUE        0x001F
#define COLOR_GREEN       0x07E0
#define COLOR_CYAN        0x07FF
#define COLOR_RED         0xF800
#define COLOR_MAGENTA     0xF81F
#define COLOR_YELLOW      0xFFE0
#define COLOR_WHITE       0xFFFF
#define COLOR_ORANGE      0xFD20
#define COLOR_GREENYELLOW 0xAFE5
#define COLOR_PINK        0xF81F

#ifdef __cplusplus
}
#endif

#endif

