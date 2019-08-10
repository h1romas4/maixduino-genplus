# maixduino-genplus

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX) Maixduino K210 porting

## work in progress

![image](https://raw.githubusercontent.com/h1romas4/maixduino-genplus/master/assets/progres_01.jpg)

## setup require

* [kendryte-toolchain](https://github.com/kendryte/kendryte-gnu-toolchain/releases)
* [kflash](https://github.com/kendryte/kflash.py)

## build

compile

```
git clone --recursive git@github.com:h1romas4/maixduino-genplus.git
cd maixduino-genplus
mkdir build & cd build
cmake .. -DPROJ=genplus -DSDK_ROOT=./kendryte-standalone-sdk -DTOOLCHAIN=/opt/kendryte-toolchain/bin
make
```

insert SD Card (filename and size fixed, oncoding now)

```
genplus/maixduino/fileio.c

COLUMS.BIN
```

flash

```
kflash -p /dev/ttyUSB0 -b 1500000 -B goE -s -t genplus.bin
```

# thanks!

[Genesis-Plus-GX](https://github.com/ekeeke/Genesis-Plus-GX)
