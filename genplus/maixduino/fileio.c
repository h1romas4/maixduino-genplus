#include <stdio.h>
#include <sysctl.h>
#include "shared.h"
#include "sdcard/ff.h"

int load_archive(char *filename, unsigned char *buffer, int maxsize, char *extension)
{
    printf("load rom start.\n");

    uint32_t size = 0;
    FIL file;
    FRESULT ret = FR_OK;

    if((ret = f_open(&file, "COLUMS.BIN", FA_READ)) == FR_OK) {
        ret = f_read(&file, (void *)buffer, 131072, &size);
        if(ret != FR_OK) {
            printf("Read %s err[%d]\n", "COLUMS.BIN", ret);
        }
        else {
            printf("Read :> %d bytes lenth\n", size);
        }
        f_close(&file);
    }
    printf("rom header first byte(0x53): 0x%x\n", buffer[0x100]);
    printf("rom data(COLUMS.BIN: 0x1f930: 0x41): 0x%x\n", buffer[0x1f930]);

    strncpy(extension, "BIN", 3);
    extension[3] = 0;

    printf("load rom end.\n");

    return size;
}
