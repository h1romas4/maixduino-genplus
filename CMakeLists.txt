# basic config
if (NOT PROJ)
    get_filename_component(PROJ ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
    get_filename_component(PROJ ${PROJ} NAME)
    string(REPLACE " " "_" PROJ ${PROJ})
    message(STATUS "PROJ not set, use ${PROJ} as PROJ. Also, you can set it manually. e.g. -DPROJ=hello_world")
else()
    message("PROJ = ${PROJ}")
endif ()
cmake_minimum_required(VERSION 3.0)
include(./cmake/common.cmake)
project(${PROJ} C CXX ASM)

# config self use headers
include(./cmake/macros.internal.cmake)
header_directories(${SDK_ROOT}/lib)
header_directories(${PROJ})

# compile project
add_source_files(
    ${PROJ}/core/z80.c
    ${PROJ}/core/m68kcpu.c
    ${PROJ}/core/genesis.c
    ${PROJ}/core/vdp_ctrl.c
    ${PROJ}/core/vdp_render.c
    ${PROJ}/core/system.c
    ${PROJ}/core/io_ctrl.c
    ${PROJ}/core/mem68k.c
    ${PROJ}/core/memz80.c
    ${PROJ}/core/membnk.c
    ${PROJ}/core/state.c
    ${PROJ}/core/loadrom.c
    ${PROJ}/core/input.c
    ${PROJ}/core/gamepad.c
    ${PROJ}/core/lightgun.c
    ${PROJ}/core/mouse.c
    ${PROJ}/core/activator.c
    ${PROJ}/core/xe_1ap.c
    ${PROJ}/core/teamplayer.c
    ${PROJ}/core/paddle.c
    ${PROJ}/core/sportspad.c
    ${PROJ}/core/terebi_oekaki.c
    ${PROJ}/core/graphic_board.c
    ${PROJ}/core/sound.c
    ${PROJ}/core/psg.c
    ${PROJ}/core/ym2413.c
    ${PROJ}/core/ym2612.c
    ${PROJ}/core/blip_buf.c
    ${PROJ}/core/eq.c
    ${PROJ}/core/sram.c
    ${PROJ}/core/svp.c
    ${PROJ}/core/ssp16.c
    ${PROJ}/core/ggenie.c
    ${PROJ}/core/areplay.c
    ${PROJ}/core/eeprom_93c.c
    ${PROJ}/core/eeprom_i2c.c
    ${PROJ}/core/eeprom_spi.c
    ${PROJ}/core/md_cart.c
    ${PROJ}/core/sms_cart.c
    ${PROJ}/core/sms_ntsc.c
    ${PROJ}/core/md_ntsc.c
    ${PROJ}/maixduino/config.c
    ${PROJ}/maixduino/error.c
    ${PROJ}/maixduino/fileio.c
    ${PROJ}/maixduino/scrc32.c
    ${PROJ}/maixduino/maixduino.c
    ${PROJ}/maixduino/lcd/lcd.c
    ${PROJ}/maixduino/lcd/st7789.c
    ${PROJ}/maixduino/sdcard/sdcard.c
    ${PROJ}/maixduino/sdcard/ff.c
    ${PROJ}/maixduino/sdcard/diskio.c
    ${PROJ}/maixduino/main.c
)
add_compile_flags(C
    -DLSB_FIRST
    -DUSE_16BPP_RENDERING
    -DMAXROMSIZE=131072
    -DHAVE_ALLOCA_H
    -DUSE_DYNAMIC_ALLOC
    -DMAIXDUINO
    -fomit-frame-pointer
    -Wno-strict-aliasing
)
include(./cmake/executable.cmake)
