[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9685

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9685/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9685는 RGBA(Red/Green/Blue/Amber) 컬러 백라이트 애플리케이션에 최적화된 I2C 버스 제어 16채널 LED 컨트롤러입니다. 각 LED 출력에는 자체 12비트 분해능(4096단계) 고정 주파수 개별 PWM 컨트롤러가 있습니다.
LED가 특정 밝기 값으로 설정되도록 0%에서 100%까지 조정 가능한 듀티 사이클과 함께 24Hz에서 1526Hz의 일반적인 프로그래밍 가능한 주파수에서. 모든 출력은 동일한 PWM 주파수로 설정됩니다.각 LED 출력을 켜거나 끄거나(PWM 제어 없음) 개별 PWM 컨트롤러 값으로 설정할 수 있습니다. LED 출력 드라이버는 5V에서 25mA 전류 싱크 기능이 있는 오픈 드레인 또는 5V에서 25mA 싱크, 10mA 소스 기능이 있는 토템 폴로 프로그래밍됩니다. PCA9685는 2.3V의 공급 전압 범위에서 작동합니다. 최대 5.5V이고 입력 및 출력은 5.5V 허용 오차입니다. LED는 LED 출력(최대 25mA, 5.5V)에 직접 연결하거나 외부 드라이버와 더 큰 전류 또는 더 높은 전압 LED를 위한 최소한의 개별 부품으로 제어할 수 있습니다. RGB 또는 RGBA LED 드라이버, LED에 사용할 수 있습니다. 상태 정보, LED 디스플레이, LCD 백라이트, 휴대폰 또는 핸드헬드 장치용 키패드 백라이트 등.

LibDriver PCA9685는 LibDriver에서 출시한 PCA9685의 전체 기능 드라이버입니다. PCA9685는 pwm 출력 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver PCA9685의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver PCA9685용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver PCA9685드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver PCA9685프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver PCA9685오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 PCA9685데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/pca9685/index.html](https://www.libdriver.com/docs/pca9685/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.