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
#include <bsp.h>
#include <sysctl.h>
#include "lcd.h"
#include "shared.h"
#include "md_ntsc.h"
#include "sms_ntsc.h"

#define PLL1_OUTPUT_FREQ 400000000UL

md_ntsc_t *md_ntsc;
sms_ntsc_t *sms_ntsc;

struct _zbank_memory_map zbank_memory_map[256];

int main(void)
{
    // The AI SRAM memory is only accessible if the following conditions are met:
    // PLL1 enabled and clock system configuration is correct
    // KPU not performing neural network calculations
    sysctl_pll_set_freq(SYSCTL_PLL1, PLL1_OUTPUT_FREQ);
    sysctl_clock_enable(SYSCTL_CLOCK_AI);

    system_init();

    lcd_begin();
    lcd_fill_rectangle(100, 100, 200, 200, 0xff00);

    printf("hello, lcd world!\n");
    while(1)
        continue;
    return 0;
}
