# maixduino-genplus

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX) Maixduino K210 porting

## work in progress

![image](https://raw.githubusercontent.com/h1romas4/maixduino-genplus/master/assets/progress_02.jpg)

[https://www.youtube.com/watch?v=VV0wlbNg2Bo](https://www.youtube.com/watch?v=VV0wlbNg2Bo)

[https://www.youtube.com/watch?v=yvkTfdkFSPQ](https://www.youtube.com/watch?v=yvkTfdkFSPQ)

## setup require

* [kendryte-toolchain](https://github.com/kendryte/kendryte-gnu-toolchain/releases)
* [kflash](https://github.com/kendryte/kflash.py)

## build

**compile**

```
git clone --recursive git@github.com:h1romas4/maixduino-genplus.git
cd maixduino-genplus
mkdir build && cd build
cmake .. -DPROJ=genplus -DSDK_ROOT=./kendryte-standalone-sdk -DTOOLCHAIN=/opt/kendryte-toolchain/bin
make
```

**insert SD card with COLUMS.BIN** (filename and size fixed, oncoding now)

genplus/maixduino/fileio.c
```
if((ret = f_open(&file, "COLUMS.BIN", FA_READ)) == FR_OK) {
    ret = f_read(&file, (void *)buffer, 131072, &size);
```

CMakeLists.txt
```
    -DMAXROMSIZE=655360
```

**flash**

```
kflash -p /dev/ttyUSB0 -b 1500000 -B goE -s -t genplus.bin
```

# thanks!

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX)
