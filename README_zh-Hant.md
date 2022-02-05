[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver PCA9685

[![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/pca9685/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9685是一款由I²C總線控制的16通道LED控制器，最適合紅色/綠色/藍色/琥珀色(RGBA)彩色背光應用。每個LED輸出各自帶有12位分辨率(4096級)固定頻率的獨立PWM控制器，該控制器工作在24 Hz至1526 Hz的可編程頻率範圍內，佔空比從0 %至100 %可調，允許將LED設為特定的亮度值。所有輸出均設為相同的PWM頻率。每個LED輸出可以是關、開(無PWM控制)或按獨立PWM控制器的值設置。 LED輸出驅動器可編程為開漏極或圖騰柱，5 V情況下開漏極具有25 mA的灌電流能力，圖騰柱具有25 mA灌電流、10 mA拉電流能力。 PCA9685的工作電源電壓範圍為2.3 V至5.5 V，輸入和輸出容許5.5 V的電壓。 LED可直接連接至LED輸出(最高25 mA，5.5 V)，或通過外部驅動器和最少量的分離組件(用於更大電流或更高電壓的LED)控制。它可用於 RGB 或 RGBA LED 驅動器、LED 狀態信息、LED 顯示器、LCD 背光、蜂窩電話或手持設備的鍵盤背光等。

LibDriver PCA9685是LibDriver推出的PCA9685的全功能驅動，該驅動提供PWM輸出等功能。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver PCA9685的源文件。

/interface目錄包含了LibDriver PCA9685與平台無關的IIC總線模板。

/test目錄包含了LibDriver PCA9685驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver PCA9685編程範例。

/doc目錄包含了LibDriver PCA9685離線文檔。

/datasheet目錄包含了PCA9685數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，/interface目錄和/example目錄加入工程。

### 使用

#### example basic

```C
volatile uint8_t res;
volatile uint32_t i, times;
pca9685_address_t address;
pca9685_channel_t channel;

address = PCA9685_ADDRESS_A000000;
channel = PCA9685_CHANNEL_0;
times = 10;

res = pca9685_basic_init(address, 50);
if (res)
{
    return 1;
}

...

for (i = 1; i < times + 1; i++)
{
    res = pca9685_basic_write(channel, 0.0f, 2.5f + (float)(i) / (float)(times) * 10.0f);
    if (res)
    {
        pca9685_basic_deinit();

        return 1;
    }

    pca9685_interface_debug_print("pca9685: set channel %d %0.2f degrees.\n", channel, (float)(i) / (float)(times) * 180.0f);

    pca9685_interface_delay_ms(1000);
    
    ...
}

...

pca9685_basic_deinit();

return 0;
```

### 文檔

在線文檔: https://www.libdriver.com/docs/pca9685/index.html

離線文檔: /doc/html/index.html

### 貢獻

請聯繫lishifenging@outlook.com

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com