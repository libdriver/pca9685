### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: OE GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(pca9685 REQUIRED)
```

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
./pca9685 -i

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
./pca9685 -p

pca9685: SCL connected to GPIO3(BCM).
pca9685: SDA connected to GPIO2(BCM).
pca9685: OE connected to GPIO17(BCM).
```

```shell
./pca9685 -t reg --addr=0

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
pca9685: set addr 0x67.
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
pca9685: set prescaler 0x59.
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
pca9685: set subaddress 1 0x68.
pca9685: check subaddress 1 ok.
pca9685: pca9685_set_subaddress_2/pca9685_get_subaddress_2 test.
pca9685: set subaddress 2 0x72.
pca9685: check subaddress 2 ok.
pca9685: pca9685_set_subaddress_3/pca9685_get_subaddress_3 test.
pca9685: set subaddress 3 0x50.
pca9685: check subaddress 3 ok.
pca9685: pca9685_set_all_call_address/pca9685_get_all_call_address test.
pca9685: set all call address 0xFE.
pca9685: check all call address ok.
pca9685: pca9685_output_frequency_convert_to_register/pca9685_output_frequency_convert_to_data test.
pca9685: set output frequency 842.
pca9685: check output frequency 872.
pca9685: pca9685_pwm_convert_to_register/pca9685_pwm_convert_to_data test.
pca9685: set delay percent 12.50.
pca9685: set high duty cycle percent 54.60.
pca9685: on_count is 0x0200.
pca9685: off_count is 0x0ABC.
pca9685: check delay percent 12.50.
pca9685: check high duty cycle percent 54.59.
pca9685: pca9685_write_channel/pca9685_read_channel test.
pca9685: set channel 0.
pca9685: set on_count 0x04CD.
pca9685: set off_count 0x0587.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 1.
pca9685: set on_count 0x07AB.
pca9685: set off_count 0x099D.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 2.
pca9685: set on_count 0x06FB.
pca9685: set off_count 0x08DE.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 3.
pca9685: set on_count 0x0146.
pca9685: set off_count 0x01C2.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 4.
pca9685: set on_count 0x02C2.
pca9685: set off_count 0x0316.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 5.
pca9685: set on_count 0x07F8.
pca9685: set off_count 0x0B13.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 6.
pca9685: set on_count 0x01E8.
pca9685: set off_count 0x07CF.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 7.
pca9685: set on_count 0x038D.
pca9685: set off_count 0x0B03.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 8.
pca9685: set on_count 0x055A.
pca9685: set off_count 0x0688.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 9.
pca9685: set on_count 0x0263.
pca9685: set off_count 0x0496.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 10.
pca9685: set on_count 0x079F.
pca9685: set off_count 0x0C68.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 11.
pca9685: set on_count 0x079A.
pca9685: set off_count 0x0B00.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 12.
pca9685: set on_count 0x0532.
pca9685: set off_count 0x053F.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 13.
pca9685: set on_count 0x07B7.
pca9685: set off_count 0x09E8.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 14.
pca9685: set on_count 0x0458.
pca9685: set off_count 0x04FB.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: set channel 15.
pca9685: set on_count 0x015A.
pca9685: set off_count 0x027F.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: pca9685_write_all_channel/pca9685_read_all_channel test.
pca9685: set on_count 0x015D.
pca9685: set off_count 0x0262.
pca9685: check on_count ok.
pca9685: check off_count ok.
pca9685: finish register test.
```

```shell
./pca9685 -t write --addr=0 --channel=0 --times=10

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
./pca9685 -e write --addr=0 --channel=0 --times=10

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
./pca9685 -h

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

