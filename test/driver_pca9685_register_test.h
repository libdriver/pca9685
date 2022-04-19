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
 * @file      driver_pca9685_register_test.h
 * @brief     driver pca9685 register test header file
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

#ifndef DRIVER_PCA9685_REGISTER_TEST_H
#define DRIVER_PCA9685_REGISTER_TEST_H

#include "driver_pca9685_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pca9685_test_driver pca9685 test driver function
 * @brief    pca9685 test driver modules
 * @ingroup  pca9685_driver
 * @{
 */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pca9685_register_test(pca9685_address_t addr);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
