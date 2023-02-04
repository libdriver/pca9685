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
 * @file      driver_pca9685_register_test.c
 * @brief     driver pca9685 register test source file
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

#include "driver_pca9685_register_test.h"
#include <stdlib.h>

static pca9685_handle_t gs_handle;        /**< pca9685 handle */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pca9685_register_test(pca9685_address_t addr)
{
    uint8_t res;
    uint8_t i;
    uint8_t addr_value, addr_value_check;
    uint8_t prescaler, prescaler_check;
    uint16_t output_freq, output_freq_check;
    uint8_t reg;
    float delay_percent, high_duty_cycle_percent;
    float delay_percent_check, high_duty_cycle_percent_check;
    uint16_t on_count, off_count;
    uint16_t on_count_check, off_count_check;
    pca9685_address_t addr_pin, addr_pin_check;
    pca9685_bool_t enable;
    pca9685_output_change_t change;
    pca9685_output_driver_t driver;
    pca9685_output_disable_type_t type;
    pca9685_channel_t channel;
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
    
    /* start register test */
    pca9685_interface_debug_print("pca9685: start register test.\n");
    
    /* pca9685_set_addr/pca9685_get_addr test */
    pca9685_interface_debug_print("pca9685: pca9685_set_addr/pca9685_get_addr test.\n");
    
    addr_value = rand() % 256;
    res = pca9685_set_addr(&gs_handle, addr_value);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set addr failed.\n");
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set addr 0x%02X.\n", addr_value);
    res = pca9685_get_addr(&gs_handle, (uint8_t *)&addr_value_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set addr failed.\n");
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check addr %s.\n", addr_value == addr_value_check ? "ok" : "error");
    
    /* pca9685_set_addr_pin/pca9685_get_addr_pin test */
    pca9685_interface_debug_print("pca9685: pca9685_set_addr_pin/pca9685_get_addr_pin test.\n");
    
    for (i = 0; i < 64; i++)
    {
        addr_pin = (pca9685_address_t)(i);
        res = pca9685_set_addr_pin(&gs_handle, addr_pin);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: set addr pin failed.\n");
            
            return 1;
        }
        pca9685_interface_debug_print("pca9685: set addr pin 0x%02X.\n", addr_pin);
        res = pca9685_get_addr_pin(&gs_handle, (pca9685_address_t *)&addr_pin_check);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: get addr pin failed.\n");
            
            return 1;
        }
        pca9685_interface_debug_print("pca9685: check addr pin %s.\n", addr_pin_check == addr_pin ? "ok" : "error");
    }
    
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
    
    /* pca9685_set_prescaler/pca9685_get_prescaler test */
    pca9685_interface_debug_print("pca9685: pca9685_set_prescaler/pca9685_get_prescaler test.\n");
    
    prescaler = rand() % 200 + 3;
    res = pca9685_set_prescaler(&gs_handle, prescaler);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set pres cale failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set prescaler 0x%02X.\n", prescaler);
    res = pca9685_get_prescaler(&gs_handle, (uint8_t *)&prescaler_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get prescaler failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check prescaler %s.\n", prescaler == prescaler_check ? "ok" : "error");
    
    /* set sleep mode */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        
        return 1;
    }
    pca9685_interface_delay_ms(2);
    
    /* pca9685_set_restart/pca9685_get_restart test */
    pca9685_interface_debug_print("pca9685: pca9685_set_restart/pca9685_get_restart test.\n");
    
    /* disable restart */
    res = pca9685_set_restart(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set restart failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable restart.\n");
    res = pca9685_get_restart(&gs_handle, (pca9685_bool_t *)&enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get restart failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check restart %s.\n", PCA9685_BOOL_FALSE == enable ? "ok" : "error");
    
    /* enable restart */
    res = pca9685_set_restart(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set restart failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable restart.\n");
    pca9685_interface_delay_ms(10);
    res = pca9685_get_restart(&gs_handle, (pca9685_bool_t *)&enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get restart failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check restart %s.\n", PCA9685_BOOL_FALSE == enable ? "ok" : "error");
    
    /* pca9685_set_external_clock_pin/pca9685_get_external_clock_pin test */
    pca9685_interface_debug_print("pca9685: pca9685_set_external_clock_pin/pca9685_get_external_clock_pin test.\n");
    
    /* disable */
    res = pca9685_set_external_clock_pin(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set external clock pin failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable external clock pin.\n");
    res = pca9685_get_external_clock_pin(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get external clock pin failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check external clock pin %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* pca9685_set_register_auto_increment/pca9685_get_register_auto_increment test */
    pca9685_interface_debug_print("pca9685: pca9685_set_register_auto_increment/pca9685_get_register_auto_increment test.\n");
    
    /* disable */
    res = pca9685_set_register_auto_increment(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set register auto increment failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable register auto increment.\n");
    res = pca9685_get_register_auto_increment(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get register auto increment failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check register auto increment %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_register_auto_increment(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set register auto increment failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable register auto increment.\n");
    res = pca9685_get_register_auto_increment(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get register auto increment failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check register auto increment %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_sleep_mode/pca9685_get_sleep_mode test */
    pca9685_interface_debug_print("pca9685: pca9685_set_sleep_mode/pca9685_get_sleep_mode test.\n");
    
    /* disable */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable sleep mode.\n");
    pca9685_interface_delay_ms(2);
    res = pca9685_get_sleep_mode(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check sleep mode %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable sleep mode.\n");
    res = pca9685_get_sleep_mode(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check sleep mode %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_respond_subaddress_1/pca9685_get_respond_subaddress_1 test */
    pca9685_interface_debug_print("pca9685: pca9685_set_respond_subaddress_1/pca9685_get_respond_subaddress_1 test.\n");
    
    /* disable */
    res = pca9685_set_respond_subaddress_1(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable respond sub address 1.\n");
    res = pca9685_get_respond_subaddress_1(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond sub address 1 %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_respond_subaddress_1(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable respond sub address 1.\n");
    res = pca9685_get_respond_subaddress_1(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond sub address 1 %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_respond_subaddress_2/pca9685_get_respond_subaddress_2 test */
    pca9685_interface_debug_print("pca9685: pca9685_set_respond_subaddress_2/pca9685_get_respond_subaddress_2 test.\n");
    
    /* disable */
    res = pca9685_set_respond_subaddress_2(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable respond sub address 2.\n");
    res = pca9685_get_respond_subaddress_2(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond sub address 2 %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_respond_subaddress_2(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable respond sub address 2.\n");
    res = pca9685_get_respond_subaddress_2(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond sub address 2 %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_respond_subaddress_3/pca9685_get_respond_subaddress_3 test */
    pca9685_interface_debug_print("pca9685: pca9685_set_respond_subaddress_3/pca9685_get_respond_subaddress_3 test.\n");
    
    /* disable */
    res = pca9685_set_respond_subaddress_3(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable respond sub address 3.\n");
    res = pca9685_get_respond_subaddress_3(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond sub address 3 %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_respond_subaddress_3(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable respond sub address 3.\n");
    res = pca9685_get_respond_subaddress_3(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond sub address 3 %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_respond_all_call/pca9685_get_respond_all_call test */
    pca9685_interface_debug_print("pca9685: pca9685_set_respond_all_call/pca9685_get_respond_all_call test.\n");
    
    /* disable */
    res = pca9685_set_respond_all_call(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond all call failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable respond all call.\n");
    res = pca9685_get_respond_all_call(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond all call failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond all call %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_respond_all_call(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond all call failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable respond all call.\n");
    res = pca9685_get_respond_all_call(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get respond all call failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check respond all call %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_output_invert/pca9685_get_output_invert test */
    pca9685_interface_debug_print("pca9685: pca9685_set_output_invert/pca9685_get_output_invert test.\n");
    
    /* disable */
    res = pca9685_set_output_invert(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output invert failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: disable output invert.\n");
    res = pca9685_get_output_invert(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output invert failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output invert %s.\n", enable == PCA9685_BOOL_FALSE ? "ok" : "error");
    
    /* enable */
    res = pca9685_set_output_invert(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output invert failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: enable output invert.\n");
    res = pca9685_get_output_invert(&gs_handle, &enable);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output invert failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output invert %s.\n", enable == PCA9685_BOOL_TRUE ? "ok" : "error");
    
    /* pca9685_set_output_change/pca9685_get_output_change test */
    pca9685_interface_debug_print("pca9685: pca9685_set_output_change/pca9685_get_output_change test.\n");
    
    /* set stop change */
    res = pca9685_set_output_change(&gs_handle, PCA9685_OUTPUT_CHANGE_STOP);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output change failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output stop change.\n");
    res =pca9685_get_output_change(&gs_handle, &change);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output change failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output change %s.\n", change == PCA9685_OUTPUT_CHANGE_STOP ? "ok" : "error");
    
    /* set ack change */
    res = pca9685_set_output_change(&gs_handle, PCA9685_OUTPUT_CHANGE_ACK);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output change failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output ack change.\n");
    res =pca9685_get_output_change(&gs_handle, &change);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output change failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output change %s.\n", change == PCA9685_OUTPUT_CHANGE_ACK ? "ok" : "error");
    
    /* pca9685_set_output_driver/pca9685_get_output_driver test */
    pca9685_interface_debug_print("pca9685: pca9685_set_output_driver/pca9685_get_output_driver test.\n");
    
    /* open drain */
    res = pca9685_set_output_driver(&gs_handle, PCA9685_OUTPUT_DRIVER_OPEN_DRAIN);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output driver failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output driver open drain.\n");
    res = pca9685_get_output_driver(&gs_handle, &driver);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output driver failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output driver %s.\n", driver == PCA9685_OUTPUT_DRIVER_OPEN_DRAIN ? "ok" : "error");
    
    /* totem pole */
    res = pca9685_set_output_driver(&gs_handle, PCA9685_OUTPUT_DRIVER_TOTEM_POLE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output driver failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output driver totem pole.\n");
    res = pca9685_get_output_driver(&gs_handle, &driver);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output driver failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output driver %s.\n", driver == PCA9685_OUTPUT_DRIVER_TOTEM_POLE ? "ok" : "error");
    
    /* pca9685_set_output_disable_type/pca9685_get_output_disable_type test */
    pca9685_interface_debug_print("pca9685: pca9685_set_output_disable_type/pca9685_get_output_disable_type test.\n");
    
    /* low */
    res = pca9685_set_output_disable_type(&gs_handle, PCA9685_OUTPUT_DISABLE_TYPE_LEDN_LOW);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output disable type low.\n");
    res = pca9685_get_output_disable_type(&gs_handle, &type);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output disable type %s.\n", type == PCA9685_OUTPUT_DISABLE_TYPE_LEDN_LOW ? "ok" : "error");
    
    /* low or high impedance */
    res = pca9685_set_output_disable_type(&gs_handle, PCA9685_OUTPUT_DISABLE_TYPE_OUTDRV_1_LEDN_LOW_OUTDRV_0_HIGH_IMPEDANCE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output disable type low or high impedance.\n");
    res = pca9685_get_output_disable_type(&gs_handle, &type);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output disable type %s.\n", type == PCA9685_OUTPUT_DISABLE_TYPE_OUTDRV_1_LEDN_LOW_OUTDRV_0_HIGH_IMPEDANCE ? "ok" : "error");
    
    /* high impedance */
    res = pca9685_set_output_disable_type(&gs_handle, PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output disable type high impedance.\n");
    res = pca9685_get_output_disable_type(&gs_handle, &type);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output disable type %s.\n", type == PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE ? "ok" : "error");
    
    /* pca9685_set_subaddress_1/pca9685_get_subaddress_1 test */
    pca9685_interface_debug_print("pca9685: pca9685_set_subaddress_1/pca9685_get_subaddress_1 test.\n");
    
    addr_value = rand() % 256;
    addr_value &= ~(1 << 0);
    res = pca9685_set_subaddress_1(&gs_handle, addr_value);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set sub address 1 0x%02X.\n", addr_value);
    res = pca9685_get_subaddress_1(&gs_handle, (uint8_t *)&addr_value_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check sub address 1 %s.\n", addr_value_check == addr_value ? "ok" : "error");
    
    /* pca9685_set_subaddress_2/pca9685_get_subaddress_2 test */
    pca9685_interface_debug_print("pca9685: pca9685_set_subaddress_2/pca9685_get_subaddress_2 test.\n");
    
    addr_value = rand() % 256;
    addr_value &= ~(1 << 0);
    res = pca9685_set_subaddress_2(&gs_handle, addr_value);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set sub address 2 0x%02X.\n", addr_value);
    res = pca9685_get_subaddress_2(&gs_handle, (uint8_t *)&addr_value_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check sub address 2 %s.\n", addr_value_check == addr_value ? "ok" : "error");
    
    /* pca9685_set_subaddress_3/pca9685_get_subaddress_3 test */
    pca9685_interface_debug_print("pca9685: pca9685_set_subaddress_3/pca9685_get_subaddress_3 test.\n");
    
    addr_value = rand() % 256;
    addr_value &= ~(1 << 0);
    res = pca9685_set_subaddress_3(&gs_handle, addr_value);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set sub address 3 0x%02X.\n", addr_value);
    res = pca9685_get_subaddress_3(&gs_handle, (uint8_t *)&addr_value_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check sub address 3 %s.\n", addr_value_check == addr_value ? "ok" : "error");
    
    /* pca9685_set_all_call_address/pca9685_get_all_call_address test */
    pca9685_interface_debug_print("pca9685: pca9685_set_all_call_address/pca9685_get_all_call_address test.\n");
    
    addr_value = rand() % 256;
    addr_value &= ~(1 << 0);
    res = pca9685_set_all_call_address(&gs_handle, addr_value);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set all call address failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set all call address 0x%02X.\n", addr_value);
    res = pca9685_get_all_call_address(&gs_handle, (uint8_t *)&addr_value_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: get all call address failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check all call address %s.\n", addr_value_check == addr_value ? "ok" : "error");
    
    /* pca9685_output_frequency_convert_to_register/pca9685_output_frequency_convert_to_data test */
    pca9685_interface_debug_print("pca9685: pca9685_output_frequency_convert_to_register/pca9685_output_frequency_convert_to_data test.\n");
    
    output_freq = rand() % (1526 - 24) + 24;
    res = pca9685_output_frequency_convert_to_register(&gs_handle, PCA9685_OSCILLATOR_INTERNAL_FREQUENCY, output_freq, (uint8_t *)&reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: output frequency convert to register failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set output frequency %d.\n", output_freq);
    res = pca9685_output_frequency_convert_to_data(&gs_handle, PCA9685_OSCILLATOR_INTERNAL_FREQUENCY, reg, (uint16_t *)&output_freq_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: output frequency convert to data failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check output frequency %d.\n", output_freq_check);
    
    /* pca9685_pwm_convert_to_register/pca9685_pwm_convert_to_data test */
    pca9685_interface_debug_print("pca9685: pca9685_pwm_convert_to_register/pca9685_pwm_convert_to_data test.\n");
    
    delay_percent = rand() % 10 + 10.5f;
    high_duty_cycle_percent = rand() % 50 + 5.6f;
    res = pca9685_pwm_convert_to_register(&gs_handle, delay_percent, high_duty_cycle_percent, (uint16_t *)&on_count, (uint16_t *)&off_count);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: pwm convert to register failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set delay percent %0.2f.\n", delay_percent);
    pca9685_interface_debug_print("pca9685: set high duty cycle percent %0.2f.\n", high_duty_cycle_percent);
    pca9685_interface_debug_print("pca9685: on_count is 0x%04X.\n", on_count);
    pca9685_interface_debug_print("pca9685: off_count is 0x%04X.\n", off_count);
    res = pca9685_pwm_convert_to_data(&gs_handle, on_count, off_count, (float *)&delay_percent_check, (float *)&high_duty_cycle_percent_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: pwm convert to data failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check delay percent %0.2f.\n", delay_percent_check);
    pca9685_interface_debug_print("pca9685: check high duty cycle percent %0.2f.\n", high_duty_cycle_percent_check);
    
    /* pca9685_write_channel/pca9685_read_channel test */
    pca9685_interface_debug_print("pca9685: pca9685_write_channel/pca9685_read_channel test.\n");
    
    for (i = 0; i < 16; i++)
    {
        channel = (pca9685_channel_t)(i);
        on_count = rand() % 2048;
        off_count = on_count + rand() % 2048;
        res = pca9685_write_channel(&gs_handle, channel, on_count, off_count);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: write channel failed.\n");
            (void)pca9685_deinit(&gs_handle);
            
            return 1;
        }
        pca9685_interface_debug_print("pca9685: set channel %d.\n", i);
        pca9685_interface_debug_print("pca9685: set on_count 0x%04X.\n", on_count);
        pca9685_interface_debug_print("pca9685: set off_count 0x%04X.\n", off_count);
        res = pca9685_read_channel(&gs_handle, channel, (uint16_t *)&on_count_check, (uint16_t *)&off_count_check);
        if (res != 0)
        {
            pca9685_interface_debug_print("pca9685: read channel failed.\n");
            (void)pca9685_deinit(&gs_handle);
            
            return 1;
        }
        pca9685_interface_debug_print("pca9685: check on_count %s.\n", on_count == on_count_check ? "ok" : "error");
        pca9685_interface_debug_print("pca9685: check off_count %s.\n", off_count == off_count_check ? "ok" : "error");
    }
    
    /* pca9685_write_all_channel/pca9685_read_all_channel test */
    pca9685_interface_debug_print("pca9685: pca9685_write_all_channel/pca9685_read_all_channel test.\n");
    
    on_count = rand() % 2048;
    off_count = on_count + rand() % 2048;
    res = pca9685_write_all_channel(&gs_handle, on_count, off_count);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: write all channel failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: set on_count 0x%04X.\n", on_count);
    pca9685_interface_debug_print("pca9685: set off_count 0x%04X.\n", off_count);
    res = pca9685_read_channel(&gs_handle, PCA9685_CHANNEL_0, (uint16_t *)&on_count_check, (uint16_t *)&off_count_check);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: read all channel failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return 1;
    }
    pca9685_interface_debug_print("pca9685: check on_count %s.\n", on_count == on_count_check ? "ok" : "error");
    pca9685_interface_debug_print("pca9685: check off_count %s.\n", off_count == off_count_check ? "ok" : "error");
    
    /* finish register test */
    pca9685_interface_debug_print("pca9685: finish register test.\n");
    (void)pca9685_deinit(&gs_handle);
    
    return 0;
}
