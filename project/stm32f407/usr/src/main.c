/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-02-20
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/02/20  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_pca9685_basic.h"
#include "driver_pca9685_write_test.h"
#include "driver_pca9685_register_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     pca9685 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t pca9685(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            pca9685_info_t info;
            
            /* print pca9685 info */
            pca9685_info(&info);
            pca9685_interface_debug_print("pca9685: chip is %s.\n", info.chip_name);
            pca9685_interface_debug_print("pca9685: manufacturer is %s.\n", info.manufacturer_name);
            pca9685_interface_debug_print("pca9685: interface is %s.\n", info.interface);
            pca9685_interface_debug_print("pca9685: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            pca9685_interface_debug_print("pca9685: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            pca9685_interface_debug_print("pca9685: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            pca9685_interface_debug_print("pca9685: max current is %0.2fmA.\n", info.max_current_ma);
            pca9685_interface_debug_print("pca9685: max temperature is %0.1fC.\n", info.temperature_max);
            pca9685_interface_debug_print("pca9685: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            pca9685_interface_debug_print("pca9685: SCL connected to GPIOB PIN8.\n");
            pca9685_interface_debug_print("pca9685: SDA connected to GPIOB PIN9.\n");
            pca9685_interface_debug_print("pca9685: OE connected to GPIOA PIN8.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show pca9685 help */
            
            help:
            
            pca9685_interface_debug_print("pca9685 -i\n\tshow pca9685 chip and driver information.\n");
            pca9685_interface_debug_print("pca9685 -h\n\tshow pca9685 help.\n");
            pca9685_interface_debug_print("pca9685 -p\n\tshow pca9685 pin connections of the current board.\n");
            pca9685_interface_debug_print("pca9685 -t reg -a <addr>\n\trun pca9685 register test.addr is the iic address and it can be \"00\"-\"63\".\n");
            pca9685_interface_debug_print("pca9685 -t write <times> -a <addr> -ch <channel>\n\t"
                                          "run pca9685 write test.times means test times.addr is the iic address and it can be \"00\"-\"63\".");
            pca9685_interface_debug_print("channel is the written channel and it can be \"0\"-\"15\".\n");
            pca9685_interface_debug_print("pca9685 -c basic <times> -a <addr> -ch <channel>\n\t"
                                          "run pca9685 write function.times means test times.addr is the iic address and it can be \"00\"-\"63\".");
            pca9685_interface_debug_print("channel is the written channel and it can be \"0\"-\"15\".\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                pca9685_address_t address;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if ((atoi(argv[4]) < 0) || (atoi(argv[4]) > 64))
                {
                    pca9685_interface_debug_print("pca9685: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pca9685_address_t)atoi(argv[4]);
                
                /* run reg test */
                if (pca9685_register_test(address))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* write function */
            if (strcmp("write", argv[2]) == 0)
            {
                pca9685_address_t address;
                pca9685_channel_t channel;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if ((atoi(argv[5]) < 0) || (atoi(argv[5]) > 64))
                {
                    pca9685_interface_debug_print("pca9685: iic address is invalid.\n");
                    
                    return 5;
                }
                if ((atoi(argv[7]) < 0) || (atoi(argv[7]) > 15))
                {
                    pca9685_interface_debug_print("pca9685: channel is invalid.\n");
                    
                    return 5;
                }
                address = (pca9685_address_t)atoi(argv[5]);
                channel = (pca9685_channel_t)(atoi(argv[7]));
        
                /* run write test */
                if (pca9685_servo_write_test(address, channel, atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* write function */
            if (strcmp("write", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i, times;
                pca9685_address_t address;
                pca9685_channel_t channel;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("-ch", argv[6]) != 0)
                {
                    return 5;
                }
                if ((atoi(argv[5]) < 0) || (atoi(argv[5]) > 64))
                {
                    pca9685_interface_debug_print("pca9685: iic address is invalid.\n");
                    
                    return 5;
                }
                if ((atoi(argv[7]) < 0) || (atoi(argv[7]) > 15))
                {
                    pca9685_interface_debug_print("pca9685: channel is invalid.\n");
                    
                    return 5;
                }
                address = (pca9685_address_t)atoi(argv[5]);
                channel = (pca9685_channel_t)(atoi(argv[7]));
                times = atoi(argv[3]);
                
                res = pca9685_basic_init(address, 50);
                if (res)
                {
                    return 1;
                }
                for (i = 1; i < times + 1; i++)
                {
                    /* write data */
                    res = pca9685_basic_write(channel, 0.0f, 2.5f + (float)(i) / (float)(times) * 10.0f);
                    if (res)
                    {
                        pca9685_basic_deinit();
                        
                        return 1;
                    }
                    
                    /* output data */
                    pca9685_interface_debug_print("pca9685: set channel %d %0.2f degrees.\n", channel, (float)(i) / (float)(times) * 180.0f);
                    
                    /* delay 1000 ms */
                    pca9685_interface_delay_ms(1000);
                }
                
                return pca9685_basic_deinit();
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    volatile uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register pca9685 fuction */
    shell_init();
    shell_register("pca9685", pca9685);
    uart1_print("pca9685: welcome to libdriver pca9685.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("pca9685: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("pca9685: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("pca9685: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("pca9685: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("pca9685: param is invalid.\n");
            }
            else
            {
                uart1_print("pca9685: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
