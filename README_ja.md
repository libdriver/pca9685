[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9685

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9685/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9685は、赤/緑/青/琥珀色（RGBA）カラーバックライトアプリケーション用に最適化されたI2Cバス制御の16チャンネルLEDコントローラーです。各LED出力には、動作する独自の12ビット分解能（4096ステップ）の固定周波数個別PWMコントローラーがあります。
LEDを特定の輝度値に設定できるように0％から100％まで調整可能なデューティサイクルで、標準の24 Hz〜1526Hzのプログラム可能な周波数ですべての出力が同じPWM周波数に設定されますLED出力は、オフまたはオン（PWM制御なし）にすることも、個々のPWMコントローラー値に設定することもできます。 LED出力ドライバは、5Vで25mAの電流シンク機能を備えたオープンドレイン、または5Vで25mAのシンク、10mAのソース機能を備えたトーテムポールのいずれかにプログラムされています。PCA9685は2.3Vの供給電圧範囲で動作します。 5.5 Vまでで、入力と出力は5.5Vトレラントです。 LEDは、LED出力（最大25 mA、5.5 V）に直接接続するか、外部ドライバーと、大電流または高電圧LED用の最小量のディスクリートコンポーネントで制御できます。RGBまたはRGBA LEDドライバー、LEDで使用できます。ステータス情報、LEDディスプレイ、LCDバックライト、携帯電話またはハンドヘルドデバイス用のキーパッドバックライトなど。

LibDriver PCA9685は、LibDriverによって起動されたPCA9685の全機能ドライバーです。PCA9685は、pwm出力およびその他の機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver PCA9685のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver PCA9685用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver PCA9685ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver PCA9685プログラミング例が含まれています。

/ docディレクトリには、LibDriver PCA9685オフラインドキュメントが含まれています。

/ datasheetディレクトリには、PCA9685データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/pca9685/index.html](https://www.libdriver.com/docs/pca9685/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。