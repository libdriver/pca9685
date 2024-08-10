[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9685

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9685/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9685是一款由I²C总线控制的16通道LED控制器，最适合红色/绿色/蓝色/琥珀色(RGBA)彩色背光应用。每个LED输出各自带有12位分辨率(4096级)固定频率的独立PWM控制器，该控制器工作在24Hz至1526Hz的可编程频率范围内，占空比从0%至100%可调，允许将LED设为特定的亮度值。所有输出均设为相同的PWM频率。每个LED输出可以是关、开(无PWM控制)或按独立PWM控制器的值设置。LED输出驱动器可编程为开漏模式，5V情况下开漏模式具有25mA的电流接收能力。PCA9685的工作电源电压范围为2.3V至5.5V，输入和输出容许5.5V的电压。LED可直接连接至LED输出(最高25mA，5.5V)，或通过外部驱动器和最少量的分离组件(用于更大电流或更高电压的LED)控制。它可用于 RGB 或 RGBA LED 驱动器、LED 状态信息、LED显示器、LCD背光、蜂窝电话或手持设备的键盘背光等。

LibDriver PCA9685是LibDriver推出的PCA9685的全功能驱动，该驱动提供PWM输出等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver PCA9685的源文件。

/interface目录包含了LibDriver PCA9685与平台无关的IIC总线模板。

/test目录包含了LibDriver PCA9685驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver PCA9685编程范例。

/doc目录包含了LibDriver PCA9685离线文档。

/datasheet目录包含了PCA9685数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_pca9685_basic.h"

uint8_t res;
uint32_t i, times;
pca9685_address_t address;
pca9685_channel_t channel;

address = PCA9685_ADDRESS_A000000;
channel = PCA9685_CHANNEL_0;
times = 10;

res = pca9685_basic_init(address, 50);
if (res != 0)
{
    return 1;
}

...

for (i = 1; i < times + 1; i++)
{
    res = pca9685_basic_write(channel, 0.0f, 2.5f + (float)(i) / (float)(times) * 10.0f);
    if (res != 0)
    {
        (void)pca9685_basic_deinit();

        return 1;
    }

    pca9685_interface_debug_print("pca9685: set channel %d %0.2f degrees.\n", channel, (float)(i) / (float)(times) * 180.0f);

    pca9685_interface_delay_ms(1000);
    
    ...
}

...

(void)pca9685_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/pca9685/index.html](https://www.libdriver.com/docs/pca9685/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。