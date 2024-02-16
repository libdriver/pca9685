[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9685

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9685/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der PCA9685 ist ein I2C-Bus-gesteuerter 16-Kanal-LED-Controller, der für Rot/Grün/Blau/Gelb (RGBA)-Hintergrundbeleuchtungsanwendungen optimiert ist. Jeder LED-Ausgang verfügt über einen eigenen PWM-Controller mit fester Frequenz und 12-Bit-Auflösung (4096 Schritte).
mit einer programmierbaren Frequenz von typisch 24 Hz bis 1526 Hz mit einem Tastverhältnis, das von 0 % bis 100 % einstellbar ist, damit die LED auf einen bestimmten Helligkeitswert eingestellt werden kann. Alle Ausgänge sind auf die gleiche PWM-Frequenz eingestellt Der LED-Ausgang kann aus- oder eingeschaltet sein (keine PWM-Steuerung) oder auf seinen individuellen PWM-Controller-Wert eingestellt werden. Der LED-Ausgangstreiber ist so programmiert, dass er entweder Open-Drain mit einer Stromsenke von 25 mA bei 5 V oder Totempfahl mit einer Senke von 25 mA und einer Quellenkapazität von 10 mA bei 5 V ist. Der PCA9685 arbeitet mit einem Versorgungsspannungsbereich von 2,3 V bis 5,5 V und die Ein- und Ausgänge sind 5,5 V tolerant. LEDs können direkt an den LED-Ausgang (bis zu 25 mA, 5,5 V) angeschlossen oder mit externen Treibern und einer minimalen Anzahl diskreter Komponenten für LEDs mit größerem Strom oder höherer Spannung gesteuert werden. Sie können in RGB- oder RGBA-LED-Treibern, LED, verwendet werden Statusinformationen, LED-Anzeigen, LCD-Hintergrundbeleuchtung, Tastaturbeleuchtung für Mobiltelefone oder Handheld-Geräte und so weiter.

LibDriver PCA9685 ist der Treiber mit vollem Funktionsumfang von PCA9685, der von LibDriver gestartet wurde. PCA9685 bietet PWM-Ausgabe und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver PCA9685-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver PCA9685 IIC.

/test enthält den Testcode des LibDriver PCA9685-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver PCA9685-Beispielcode.

/doc enthält das LibDriver PCA9685-Offlinedokument.

/Datenblatt enthält PCA9685-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/pca9685/index.html](https://www.libdriver.com/docs/pca9685/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.