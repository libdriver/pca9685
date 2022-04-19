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
 * @file      driver_pca9685_basic.h
 * @brief     driver pca9685 basic header file
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

#ifndef DRIVER_PCA9685_BASIC_H
#define DRIVER_PCA9685_BASIC_H

#include "driver_pca9685_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pca9685_example_driver pca9685 example driver function
 * @brief    pca9685 example driver modules
 * @ingroup  pca9685_driver
 * @{
 */

/**
 * @brief pca9685 basic example default definition
 */
#define PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_1        PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_2        PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_2        PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_RESPOND_ALL_CALL            PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_OUTPUT_INVERT               PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_OUTPUT_CHANGE               PCA9685_OUTPUT_CHANGE_STOP                        /**< stop change */
#define PCA9685_BASIC_DEFAULT_OUTPUT_DRIVER               PCA9685_OUTPUT_DRIVER_TOTEM_POLE                  /**< totem pole */
#define PCA9685_BASIC_DEFAULT_OUTPUT_DISABLE_TYPE         PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE        /**< high impedance */
#define PCA9685_BASIC_DEFAULT_ALL_CALL_ADDRESS            0xE0                                              /**< 0xE0 */
#define PCA9685_BASIC_DEFAULT_SUBADDRESS_1                0xE2                                              /**< 0xE2 */
#define PCA9685_BASIC_DEFAULT_SUBADDRESS_2                0xE4                                              /**< 0xE4 */
#define PCA9685_BASIC_DEFAULT_SUBADDRESS_3                0xE8                                              /**< 0xE8 */

/**
 * @brief     basic example init
 * @param[in] addr is the iic device address
 * @param[in] hz is the output frequency
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t pca9685_basic_init(pca9685_address_t addr, uint16_t hz);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pca9685_basic_deinit(void);

/**
 * @brief     basic example write
 * @param[in] channel is the pwm channel
 * @param[in] delay_percent is the start delay percent
 * @param[in] high_duty_cycle_percent is the pwm high duty cycle percent
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      0.0 <= delay_percent + high_duty_cycle_percent <= 100.0
 *            0.0 <= delay_percent <= 100.0
 *            0.0 <= high_duty_cycle_percent <= 100.0
 */
uint8_t pca9685_basic_write(pca9685_channel_t channel, float delay_percent, float high_duty_cycle_percent);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
