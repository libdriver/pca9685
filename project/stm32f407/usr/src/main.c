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
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     pca9685 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t pca9685(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"channel", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    pca9685_address_t addr = PCA9685_ADDRESS_A000000;
    pca9685_channel_t channel = PCA9685_CHANNEL_0;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if ((atoi(optarg) < 0) || (atoi(optarg) > 64))
                {
                    return 5;
                }
                addr = (pca9685_address_t)atoi(optarg);
                
                break;
            }
            
            /* channel */
            case 2 :
            {
                /* set the channel */
                if ((atoi(optarg) < 0) || (atoi(optarg) > 15))
                {
                    return 5;
                }
                channel = (pca9685_channel_t)(atoi(optarg));
                
                break;
            }
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (pca9685_register_test(addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_write", type) == 0)
    {
        /* run write test */
        if (pca9685_servo_write_test(addr, channel, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* basic init */
        res = pca9685_basic_init(addr, 50);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 1; i < times + 1; i++)
        {
            /* write data */
            res = pca9685_basic_write(channel, 0.0f, 2.5f + (float)(i) / (float)(times) * 10.0f);
            if (res != 0)
            {
                (void)pca9685_basic_deinit();
                
                return 1;
            }
            
            /* output data */
            pca9685_interface_debug_print("pca9685: set channel %d %0.2f degrees.\n", channel, (float)(i) / (float)(times) * 180.0f);
            
            /* delay 1000 ms */
            pca9685_interface_delay_ms(1000);
        }
        
        /* basic deinit */
        (void)pca9685_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        pca9685_interface_debug_print("Usage:\n");
        pca9685_interface_debug_print("  pca9685 (-i | --information)\n");
        pca9685_interface_debug_print("  pca9685 (-h | --help)\n");
        pca9685_interface_debug_print("  pca9685 (-p | --port)\n");
        pca9685_interface_debug_print("  pca9685 (-t reg | --test=reg) [--addr=<address>]\n");
        pca9685_interface_debug_print("  pca9685 (-t write | --test=write) [--addr=<address>] [--channel=<ch>] [--times=<num>]\n");
        pca9685_interface_debug_print("  pca9685 (-e write | --example=write) [--addr=<address>] [--channel=<ch>] [--times=<num>]\n");
        pca9685_interface_debug_print("\n");
        pca9685_interface_debug_print("Options:\n");
        pca9685_interface_debug_print("      --addr=<address>    Set the addr pin and it can be \"0\"-\"63\".([default: 0])\n");
        pca9685_interface_debug_print("      --channel=<ch>      Set the used channel and it can be \"0\"-\"15\".([default: 0])\n");
        pca9685_interface_debug_print("  -e <write>, --example=<write>\n");
        pca9685_interface_debug_print("                          Run the driver example.\n");
        pca9685_interface_debug_print("  -h, --help              Show the help.\n");
        pca9685_interface_debug_print("  -i, --information       Show the chip information.\n");
        pca9685_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        pca9685_interface_debug_print("  -t <reg | write>, --test=<reg | write>\n");
        pca9685_interface_debug_print("                          Run the driver test.\n");
        pca9685_interface_debug_print("      --times=<num>       Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        pca9685_interface_debug_print("pca9685: SCL connected to GPIOB PIN8.\n");
        pca9685_interface_debug_print("pca9685: SDA connected to GPIOB PIN9.\n");
        pca9685_interface_debug_print("pca9685: OE connected to GPIOA PIN8.\n");
        
        return 0;
    }
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
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register pca9685 function */
    shell_init();
    shell_register("pca9685", pca9685);
    uart_print("pca9685: welcome to libdriver pca9685.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("pca9685: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("pca9685: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("pca9685: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("pca9685: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("pca9685: param is invalid.\n");
            }
            else
            {
                uart_print("pca9685: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
