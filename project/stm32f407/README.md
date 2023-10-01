### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

GPIO Pin: OE PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. PCA9685

#### 3.1 Command Instruction

1. Show pca9685 chip and driver information.

   ```shell
   pca9685 (-i | --information)
   ```

2. Show pca9685 help.

   ```shell
   pca9685 (-h | --help)
   ```

3. Show pca9685 pin connections of the current board.

   ```shell
   pca9685 (-p | --port)
   ```

4. Run pca9685 register test, address is the iic address and it can be "0"-"63".

   ```shell
   pca9685 (-t reg | --test=reg) [--addr=<address>]
   ```

5. Run pca9685 write test, num means test times, address is the iic address and it can be "0"-"63", ch is the used channel and it can be "0"-"15".

   ```shell
   pca9685 (-t write | --test=write) [--addr=<address>] [--channel=<ch>] [--times=<num>]
   ```

6. Run pca9685 write function, num means test times, address is the iic address and it can be "0"-"63", ch is the used channel and it can be "0"-"15".

   ```shell
   pca9685 (-e write | --example=write) [--addr=<address>] [--channel=<ch>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
pca9685 -i

pca9685: chip is NXP PCA9685.
pca9685: manufacturer is NXP.
pca9685: interface is IIC.
pca9685: driver version is 1.0.
pca9685: min supply voltage is 2.3V.
pca9685: max supply voltage is 5.5V.
pca9685: max current is 400.00mA.
pca9685: max temperature is 85.0C.
pca9685: min temperature is -40.0C.
```

```shell
pca9685 -p

pca9685: SCL connected to GPIOB PIN8.
pca9685: SDA connected to GPIOB PIN9.
pca9685: OE connected to GPIOA PIN8.
```

```shell
pca9685 -t reg --addr=0

pca9685: chip is NXP PCA9685.
pca9685: manufacturer is NXP.
pca9685: interface is IIC.
pca9685: driver version is 1.0.
pca9685: min supply voltage is 2.3V.
pca9685: max supply voltage is 5.5V.
pca9685: max current is 400.00mA.
pca9685: max temperature is 85.0C.
pca9685: min temperature is -40.0C.
pca9685: start register test.
pca9685: pca9685_set_addr/pca9685_get_addr test.
pca9685: set addr 0xB0.
pca9685: check addr ok.
pca9685: pca9685_set_addr_pin/pca9685_get_addr_pin test.
pca9685: set addr pin 0x00.
pca9685: check addr pin ok.
pca9685: set addr pin 0x01.
pca9685: check addr pin ok.
pca9685: set addr pin 0x02.
pca9685: check addr pin ok.
pca9685: set addr pin 0x03.
pca9685: check addr pin ok.
pca9685: set addr pin 0x04.
pca9685: check addr pin ok.
pca9685: set addr pin 0x05.
pca9685: check addr pin ok.
pca9685: set addr pin 0x06.
pca9685: check addr pin ok.
pca9685: set addr pin 0x07.
pca9685: check addr pin ok.
pca9685: set addr pin 0x08.
pca9685: check addr pin ok.
pca9685: set addr pin 0x09.
pca9685: check addr pin ok.
pca9685: set addr pin 0x0A.
pca9685: check addr pin ok.
pca9685: set addr pin 0x0B.
pca9685: check addr pin ok.
pca9685: set addr pin 0x0C.
pca9685: check addr pin ok.
pca9685: set addr pin 0x0D.
pca9685: check addr pin ok.
pca9685: set addr pin 0x0E.
pca9685: check addr pin ok.
pca9685: set addr pin 0x0F.
pca9685: check addr pin ok.
pca9685: set addr pin 0x10.
pca9685: check addr pin ok.
pca9685: set addr pin 0x11.
pca9685: check addr pin ok.
pca9685: set addr pin 0x12.
pca9685: check addr pin ok.
pca9685: set addr pin 0x13.
pca9685: check addr pin ok.
pca9685: set addr pin 0x14.
pca9685: check addr pin ok.
pca9685: set addr pin 0x15.
pca9685: check addr pin ok.
pca9685: set addr pin 0x16.
pca9685: check addr pin ok.
pca9685: set addr pin 0x17.
pca9685: check addr pin ok.
pca9685: set addr pin 0x18.
pca9685: check addr pin ok.
pca9685: set addr pin 0x19.
pca9685: check addr pin ok.
pca9685: set addr pin 0x1A.
pca9685: check addr pin ok.
pca9685: set addr pin 0x1B.
pca9685: check addr pin ok.
pca9685: set addr pin 0x1C.
pca9685: check addr pin ok.
pca9685: set addr pin 0x1D.
pca9685: check addr pin ok.
pca9685: set addr pin 0x1E.
pca9685: check addr pin ok.
pca9685: set addr pin 0x1F.
pca9685: check addr pin ok.
pca9685: set addr pin 0x20.
pca9685: check addr pin ok.
pca9685: set addr pin 0x21.
pca9685: check addr pin ok.
pca9685: set addr pin 0x22.
pca9685: check addr pin ok.
pca9685: set addr pin 0x23.
pca9685: check addr pin ok.
pca9685: set addr pin 0x24.
pca9685: check addr pin ok.
pca9685: set addr pin 0x25.
pca9685: check addr pin ok.
pca9685: set addr pin 0x26.
pca9685: check addr pin ok.
pca9685: set addr pin 0x27.
pca9685: check addr pin ok.
pca9685: set addr pin 0x28.
pca9685: check addr pin ok.
pca9685: set addr pin 0x29.
pca9685: check addr pin ok.
pca9685: set addr pin 0x2A.
pca9685: check addr pin ok.
pca9685: set addr pin 0x2B.
pca9685: check addr pin ok.
pca9685: set addr pin 0x2C.
pca9685: check addr pin ok.
pca9685: set addr pin 0x2D.
pca9685: check addr pin ok.
pca9685: set addr pin 0x2E.
pca9685: check addr pin ok.
pca9685: set addr pin 0x2F.
pca9685: check addr pin ok.
pca9685: set addr pin 0x30.
pca9685: check addr pin ok.
pca9685: set addr pin 0x31.
pca9685: check addr pin ok.
pca9685: set addr pin 0x32.
pca9685: check addr pin ok.
pca9685: set addr pin 0x33.
pca9685: check addr pin ok.
pca9685: set addr pin 0x34.
pca9685: check addr pin ok.
pca9685: set addr pin 0x35.
pca9685: check addr pin ok.
pca9685: set addr pin 0x36.
pca9685: check addr pin ok.
pca9685: set addr pin 0x37.
pca9685: check addr pin ok.
pca9685: set addr pin 0x38.
pca9685: check addr pin ok.
pca9685: set addr pin 0x39.
pca9685: check addr pin ok.
pca9685: set addr pin 0x3A.
pca9685: check addr pin ok.
pca9685: set addr pin 0x3B.
pca9685: check addr pin ok.
pca9685: set addr pin 0x3C.
pca9685: check addr pin ok.
pca9685: set addr pin 0x3D.
pca9685: check addr pin ok.
pca9685: set addr pin 0x3E.
pca9685: check addr pin ok.
pca9685: set addr pin 0x3F.
pca9685: check addr pin ok.
pca9685: pca9685_set_prescaler/pca9685_get_prescaler test.
pca9685: set prescaler 0x46.
pca9685: check prescaler ok.
pca9685: pca9685_set_restart/pca9685_get_restart test.
pca9685: disable restart.
pca9685: check restart ok.
pca9685: enable restart.
pca9685: check restart ok.
pca9685: pca9685_set_external_clock_pin/pca9685_get_external_clock_pin test.
pca9685: disable external clock pin.
pca9685: check external clock pin ok.
pca9685: pca9685_set_register_auto_increment/pca9685_get_register_auto_increment test.
pca9685: disable register auto increment.
pca9685: check register auto increment ok.
pca9685: enable register auto increment.
pca9685: check register auto increment ok.
pca9685: pca9685_set_sleep_mode/pca9685_get_sleep_mode test.
pca9685: disable sleep mode.
pca9685: check sleep mode ok.
pca9685: enable sleep mode.
pca9685: check sleep mode ok.
pca9685: pca9685_set_respond_subaddress_1/pca9685_get_respond_subaddress_1 test.
pca9685: disable respond subaddress 1.
pca9685: check respond subaddress 1 ok.
pca9685: enable respond subaddress 1.
pca9685: check respond subaddress 1 ok.
pca9685: pca9685_set_respond_subaddress_2/pca9685_get_respond_subaddress_2 test.
pca9685: disable respond subaddress 2.
pca9685: check respond subaddress 2 ok.
pca9685: enable respond subaddress 2.
pca9685: check respond subaddress 2 ok.
pca9685: pca9685_set_respond_subaddress_3/pca9685_get_respond_subaddress_3 test.
pca9685: disable respond subaddress 3.
pca9685: check respond subaddress 3 ok.
pca9685: enable respond subaddress 3.
pca9685: check respond subaddress 3 ok.
pca9685: pca9685_set_respond_all_call/pca9685_get_respond_all_call test.
pca9685: disable respond all call.
pca9685: check respond all call ok.
pca9685: enable respond all call.
pca9685: check respond all call ok.
pca9685: pca9685_set_output_invert/pca9685_get_output_invert test.
pca9685: disable outoput invert.
pca9685: check outoput invert ok.
pca9685: enable outoput invert.
pca9685: check outoput invert ok.
pca9685: pca9685_set_output_change/pca9685_get_output_change test.
pca9685: set output stop change.
pca9685: check outoput change ok.
pca9685: set output ack change.
pca9685: check outoput change ok.
pca9685: pca9685_set_output_driver/pca9685_get_output_driver test.
pca9685: set output driver open drain.
pca9685: check outoput driver ok.
pca9685: set output driver totem pole.
pca9685: check outoput driver ok.
pca9685: pca9685_set_output_disable_type/pca9685_get_output_disable_type test.
pca9685: set output disable type low.
pca9685: check output disable type ok.
pca9685: set output disable type low or high impedance.
pca9685: check output disable type ok.
pca9685: set output disable type high impedance.
pca9685: check output disable type ok.
pca9685: pca9685_set_subaddress_1/pca9685_get_subaddress_1 test.
pca9685: set subaddress 1 0x48.
pca9685: check subaddress 1 ok.
pca9685: pca9685_set_subaddress_2/pca9685_get_subaddress_2 test.
pca9685: set subaddress 2 0x68.
pca9685: check subaddress 2 ok.
pca9685: pca9685_set_subaddress_3/pca9685_get_subaddress_3 test.
pca9685: set subaddress 3 0x06.
pca9685: check subaddress 3 ok.
pca9685: pca9685_set_all_call_address/pca9685_get_all_call_address test.
pca9685: set all call address 0x44.
pca9685: check all call address ok.
pca9685: pca9685_output_frequency_convert_to_register/pca9685_output_frequency_convert_to_data test.
pca9685: set output frequency 1190.
pca9685: check output frequency 1221.
pca9685: pca9685_pwm_convert_to_register/pca9685_pwm_convert_to_data test.
pca9685: set delay percent 17.50.
pca9685: set high duty cycle percent 12.60.
pca9685: on_count is 0x02CD.
pca9685: off_count is 0x04D1.
pca9685: check delay percent 17.50.
pca9685: check high duty cycle percent 12.60.
pca9685: pca9685_write_channel/pca9685_read_channel test.
pca9685: set channel 0.
pca9685: set on_count 0x07C4.
pca9685: set off_count 0x0830.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 1.
pca9685: set on_count 0x072B.
pca9685: set off_count 0x0AE5.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 2.
pca9685: set on_count 0x0661.
pca9685: set off_count 0x07C6.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 3.
pca9685: set on_count 0x07A1.
pca9685: set off_count 0x0C13.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 4.
pca9685: set on_count 0x0064.
pca9685: set off_count 0x039D.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 5.
pca9685: set on_count 0x063D.
pca9685: set off_count 0x082B.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 6.
pca9685: set on_count 0x06D2.
pca9685: set off_count 0x0987.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 7.
pca9685: set on_count 0x015A.
pca9685: set off_count 0x0393.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 8.
pca9685: set on_count 0x0768.
pca9685: set off_count 0x0D50.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 9.
pca9685: set on_count 0x00C9.
pca9685: set off_count 0x0373.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 10.
pca9685: set on_count 0x075C.
pca9685: set off_count 0x0DFB.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 11.
pca9685: set on_count 0x0230.
pca9685: set off_count 0x02F1.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 12.
pca9685: set on_count 0x0658.
pca9685: set off_count 0x0932.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 13.
pca9685: set on_count 0x0259.
pca9685: set off_count 0x0518.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 14.
pca9685: set on_count 0x04DD.
pca9685: set off_count 0x0BB9.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 15.
pca9685: set on_count 0x031B.
pca9685: set off_count 0x078C.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: pca9685_write_all_channel/pca9685_read_all_channel test.
pca9685: set on_count 0x06BB.
pca9685: set off_count 0x0CDE.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: finish register test.
```

```shell
pca9685 -t write --addr=0 --channel=0 --times=10

pca9685: chip is NXP PCA9685.
pca9685: manufacturer is NXP.
pca9685: interface is IIC.
pca9685: driver version is 1.0.
pca9685: min supply voltage is 2.3V.
pca9685: max supply voltage is 5.5V.
pca9685: max current is 400.00mA.
pca9685: max temperature is 85.0C.
pca9685: min temperature is -40.0C.
pca9685: start write test.
pca9685: set channel 0 18.00 degrees.
pca9685: set channel 0 36.00 degrees.
pca9685: set channel 0 54.00 degrees.
pca9685: set channel 0 72.00 degrees.
pca9685: set channel 0 90.00 degrees.
pca9685: set channel 0 108.00 degrees.
pca9685: set channel 0 126.00 degrees.
pca9685: set channel 0 144.00 degrees.
pca9685: set channel 0 162.00 degrees.
pca9685: set channel 0 180.00 degrees.
pca9685: set all channel 18.00 degrees.
pca9685: set all channel 36.00 degrees.
pca9685: set all channel 54.00 degrees.
pca9685: set all channel 72.00 degrees.
pca9685: set all channel 90.00 degrees.
pca9685: set all channel 108.00 degrees.
pca9685: set all channel 126.00 degrees.
pca9685: set all channel 144.00 degrees.
pca9685: set all channel 162.00 degrees.
pca9685: set all channel 180.00 degrees.
pca9685: finish write test.
```

```shell
pca9685 -e write --addr=0 --channel=0 --times=10

pca9685: set channel 0 18.00 degrees.
pca9685: set channel 0 36.00 degrees.
pca9685: set channel 0 54.00 degrees.
pca9685: set channel 0 72.00 degrees.
pca9685: set channel 0 90.00 degrees.
pca9685: set channel 0 108.00 degrees.
pca9685: set channel 0 126.00 degrees.
pca9685: set channel 0 144.00 degrees.
pca9685: set channel 0 162.00 degrees.
pca9685: set channel 0 180.00 degrees.
```

```shell
pca9685 -h

Usage:
  pca9685 (-i | --information)
  pca9685 (-h | --help)
  pca9685 (-p | --port)
  pca9685 (-t reg | --test=reg) [--addr=<address>]
  pca9685 (-t write | --test=write) [--addr=<address>] [--channel=<ch>] [--times=<num>]
  pca9685 (-e write | --example=write) [--addr=<address>] [--channel=<ch>] [--times=<num>]

Options:
      --addr=<address>    Set the addr pin and it can be "0"-"63".([default: 0])
      --channel=<ch>      Set the used channel and it can be "0"-"15".([default: 0])
  -e <write>, --example=<write>
                          Run the driver example.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
  -p, --port              Display the pin connections of the current board.
  -t <reg | write>, --test=<reg | write>
                          Run the driver test.
      --times=<num>       Set the running times.([default: 3])
```

