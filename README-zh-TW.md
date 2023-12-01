# KeepUrLearn

[English](./README.md) ｜繁體中文  
以C語言為基礎，用來保持 uLearn.nfu session上線的程式

## 編譯

1. Clone 本 repo
2. 安裝 `libcurl` 透過 [該網站](https://curl.se/download.html) 或從各發行版的套件安裝器安裝
3. 連結 `libcurl`
4. 編譯 `./src/main.c`

```shell
gcc main.c -O2 -lcurl
```

## 執行

### 輸出範例

```shell
$ ./a.out 
輸入已登入的session cookie：V2-1-9bd0c346-2b13-4fce-a7a2-9828d2c2e0ca.NTA4OTY.1701098676700.QBUNwSHVD3u5YhKwroS-VRTsCDE

更新完成！已保持的session cookie為：
V2-1-9bd0c346-2b13-4fce-a7a2-9828d2c2e0ca.NTA4OTY.1701098676700.QBUNwSHVD3u5YhKwroS-VRTsCDE

下一次更新為30秒後
```

> [!NOTE]  
> **不產生任何輸出，只持續與網站進行http請求**

## 授權

本軟體遵守[MIT](./LICENSE)授權條款。
