# KeepUrLearn

English ｜[繁體中文](./README-zh-TW.md)  
A C based program used for keep uLearn.nfu session uptime

## Build

1. Clone this repo
2. Install `libcurl` through [here](https://curl.se/download.html) or install from distro packages
3. Link `libcurl`
4. Compile `./src/main.c`

```shell
gcc main.c -O2 -lcurl
```

## Running

### Example output

```shell
$ ./a.out 
輸入已登入的session cookie：V2-1-9bd0c346-2b13-4fce-a7a2-9828d2c2e0ca.NTA4OTY.1701098676700.QBUNwSHVD3u5YhKwroS-VRTsCDE

更新完成！已保持的session cookie為：
V2-1-9bd0c346-2b13-4fce-a7a2-9828d2c2e0ca.NTA4OTY.1701098676700.QBUNwSHVD3u5YhKwroS-VRTsCDE
```

> [!NOTE]  
> **Generates no output, keep http request only**

## License

Licensed under [MIT](./LICENSE)
