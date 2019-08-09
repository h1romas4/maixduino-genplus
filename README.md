# maixduino-genplus

```
cd build
cmake .. -DPROJ=genplus -DSDK_ROOT=./kendryte-standalone-sdk -DTOOLCHAIN=/opt/kendryte-toolchain/bin
```

```
kflash -p /dev/ttyUSB0 -b 1500000 -B goE -s -t genplus.bin
```
