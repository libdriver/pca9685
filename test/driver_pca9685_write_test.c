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
 * @file      driver_pca9685_write_test.c
 * @brief     driver pca9685 write test source file
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

#include "driver_pca9685_write_test.h"

static pca9685_handle_t gs_handle;        /**< pca9685 handle */

/**
 * @brief     servo write test
 * @param[in] addr is the iic device address
 * @param[in] channel is the written channel
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pca9685_servo_write_test(pca9685_address_t addr, pca9685_channel_t channel, uint32_t times)
{
    uint8_t res;
    uint8_t reg;
    uint16_t on_count, off_count;
    uint32_t i;
    pca9685_info_t info;
    
    /* link interface function */
    DRIVER_PCA9685_LINK_INIT(&gs_handle, pca9685_handle_t);
    DRIVER_PCA9685_LINK_IIC_INIT(&gs_handle, pca9685_interface_iic_init);
    DRIVER_PCA9685_LINK_IIC_DEINIT(&gs_handle, pca9685_interface_iic_deinit);
    DRIVER_PCA9685_LINK_IIC_READ(&gs_handle, pca9685_interface_iic_read);
    DRIVER_PCA9685_LINK_IIC_WEITE(&gs_handle, pca9685_interface_iic_write);
    DRIVER_PCA9685_LINK_OE_GPIO_INIT(&gs_handle, pca9685_interface_oe_init);
    DRIVER_PCA9685_LINK_OE_GPIO_DEINIT(&gs_handle, pca9685_interface_oe_deinit);
    DRIVER_PCA9685_LINK_OE_GPIO_WRITE(&gs_handle, pca9685_interface_oe_write);
    DRIVER_PCA9685_LINK_DELAY_MS(&gs_handle, pca9685_interface_delay_ms);
    DRIVER_PCA9685_LINK_DEBUG_PRINT(&gs_handle, pca9685_interface_debug_print);
    
    /* get information */
    res = pca9685_info(&info);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        pca9685_interface_debug_print("pca9685: chip is %s.\n", info.chip_name);
        pca9685_interface_debug_print("pca9685: manufacturer is %s.\n", info.manufacturer_name);
        pca9685_interface_debug_print("pca9685: interface is %s.\n", info.interface);
        pca9685_interface_debug_print("pca9685: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pca9685_interface_debug_print("pca9685: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pca9685_interface_debug_print("pca9685: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pca9685_interface_debug_print("pca9685: max current is %0.2fmA.\n", info.max_current_ma);
        pca9685_interface_debug_print("pca9685: max temperature is %0.1fC.\n", info.temperature_max);
        pca9685_interface_debug_print("pca9685: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start write test */
    pca9685_interface_debug_print("pca9685: start write test.\n");
    
    /* set addr pin */
    res = pca9685_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set addr pin failed.\n");
        
        return 1;
    }
    
    /* pca9685 init */
    res = pca9685_init(&gs_handle);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: init failed.\n");
        
        return 1;
    }
    
    /* inactive */
    res = pca9685_set_active(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set active failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set sleep mode */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 50Hz */
    res = pca9685_output_frequency_convert_to_register(&gs_handle, PCA9685_OSCILLATOR_INTERNAL_FREQUENCY, 50, (uint8_t *)&reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: output frequency convert to register failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set pre scale */
    res = pca9685_set_prescaler(&gs_handle, reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set pre scale failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable external clock pin */
    res = pca9685_set_external_clock_pin(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set external clock pin failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable auto increment */
    res = pca9685_set_register_auto_increment(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set register auto increment failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable respond sub address 1 */
    res = pca9685_set_respond_subaddress_1(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable respond sub address 2 */
    res = pca9685_set_respond_subaddress_2(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable respond sub address 3 */
    res = pca9685_set_respond_subaddress_3(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable respond all call */
    res = pca9685_set_respond_all_call(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond all call failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable output invert */
    res = pca9685_set_output_invert(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output invert failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* stop output change */
    res = pca9685_set_output_change(&gs_handle, PCA9685_OUTPUT_CHANGE_STOP);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output change failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* totem pole driver */
    res = pca9685_set_output_driver(&gs_handle, PCA9685_OUTPUT_DRIVER_TOTEM_POLE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output driver failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* high impedance */
    res = pca9685_set_output_disable_type(&gs_handle, PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set sleep mode */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* active */
    res = pca9685_set_active(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set active failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    for (i = 1; i < times + 1; i++)
    {
        /* convert data */
        res = pca9685_pwm_convert_to_register(&gs_handle, 0.0f, 2.5f + (float)(i) / (float)(times) * 10.0f,
                                              (uint16_t *)&on_count, (uint16_t *)&off_count);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: convert to register failed.\n");
            (void)pca9685_deinit(&gs_handle);
            
            return 1;
        }
        
        /* write channel */
        res = pca9685_write_channel(&gs_handle, channel, on_count, off_count);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: write channel failed.\n");
            (void)pca9685_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output data */
        pca9685_interface_debug_print("pca9685: set channel %d %0.2f degrees.\n", channel, (float)(i) / (float)(times) * 180.0f);
        
        /* delay 1000 ms */
        pca9685_interface_delay_ms(1000);
    }
    
    /* output */
    for (i = 1; i < times + 1; i++)
    {
        /* convert data */
        res = pca9685_pwm_convert_to_register(&gs_handle, 0.0f, 2.5f + (float)(i) / (float)(times) * 10.0f,
                                              (uint16_t *)&on_count, (uint16_t *)&off_count);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: convert to register failed.\n");
            (void)pca9685_deinit(&gs_handle);
            
            return 1;
        }
        
        /* write all channel */
        res = pca9685_write_all_channel(&gs_handle, on_count, off_count);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: write all channel failed.\n");
            (void)pca9685_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output data */
        pca9685_interface_debug_print("pca9685: set all channel %0.2f degrees.\n", (float)(i) / (float)(times) * 180.0f);
        
        /* delay 1000 ms */
        pca9685_interface_delay_ms(1000);
    }
    
    /* inactive */
    res = pca9685_set_active(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set active failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish write test */
    pca9685_interface_debug_print("pca9685: finish write test.\n");
    (void)pca9685_deinit(&gs_handle);
    
    return 0;
}
