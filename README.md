# maixduino-genplus

```
git clone git@github.com:h1romas4/maixduino-genplus.git
cd maixduino-genplus
mkdir build & cd build
cmake .. -DPROJ=genplus -DSDK_ROOT=./kendryte-standalone-sdk -DTOOLCHAIN=/opt/kendryte-toolchain/bin
```

```
kflash -p /dev/ttyUSB0 -b 1500000 -B goE -s -t genplus.bin
```
