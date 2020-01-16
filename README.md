# maixduino-genplus

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX) Maixduino K210 porting

## Demo

![image](https://raw.githubusercontent.com/h1romas4/maixduino-genplus/master/assets/progress_02.jpg)

[https://www.youtube.com/watch?v=VV0wlbNg2Bo](https://www.youtube.com/watch?v=VV0wlbNg2Bo)

[https://www.youtube.com/watch?v=yvkTfdkFSPQ](https://www.youtube.com/watch?v=yvkTfdkFSPQ)

LCD bitmap trancefar is not in time due to SPI clock slow.

## Require

* [Kendryte GNU Toolchain v8.2.0-20190213](https://github.com/kendryte/kendryte-gnu-toolchain/releases/tag/v8.2.0-20190213)
* [kflash](https://github.com/kendryte/kflash.py)

```
$ pwd
/opt/kendryte-toolchain/bin
$ ./riscv64-unknown-elf-gcc -v
gcc version 8.2.0 (GCC)
$ kflash -h
...
positional arguments:
  firmware              firmware bin path
...
```

## Build

![](https://github.com/h1romas4/maixduino-genplus/workflows/K210%20CI/badge.svg)

**Compile**

```
git clone --recursive https://github.com/h1romas4/maixduino-genplus.git
cd maixduino-genplus
mkdir build && cd build
# set -DTOOLCHAIN to directory Kendryte GNU Toolchain bin path
cmake .. -DPROJ=genplus -DSDK_ROOT=./kendryte-standalone-sdk -DTOOLCHAIN=/opt/kendryte-toolchain/bin
make
```

**Insert SD card with COLUMS.BIN** (filename and size fixed, oncoding now)

genplus/maixduino/fileio.c
```
if((ret = f_open(&file, "COLUMS.BIN", FA_READ)) == FR_OK) {
    ret = f_read(&file, (void *)buffer, 131072, &size);
```

CMakeLists.txt
```
    -DMAXROMSIZE=655360
```

**Flash**

```
kflash -p /dev/ttyUSB0 -b 1500000 -B goE -s -t genplus.bin
```

## License

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX/blob/master/LICENSE.txt) License

## Thanks!

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX)
