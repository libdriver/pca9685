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
 * @file      driver_pca9685.h
 * @brief     driver pca9685 header file
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

#ifndef DRIVER_PCA9685_H
#define DRIVER_PCA9685_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pca9685_driver pca9685 driver function
 * @brief    pca9685 driver modules
 * @{
 */

/**
 * @addtogroup pca9685_base_driver
 * @{
 */

/**
 * @brief pca9685 internal oscillator frequency
 */
#ifndef PCA9685_OSCILLATOR_INTERNAL_FREQUENCY
    #define PCA9685_OSCILLATOR_INTERNAL_FREQUENCY 25000000        /**< 25MHz */
#endif

/**
 * @brief pca9685 address enumeration definition
 */
typedef enum
{
    PCA9685_ADDRESS_A000000 = 0x00,        /**< A5A4A3A2A1A0 000000 */
    PCA9685_ADDRESS_A000001 = 0x01,        /**< A5A4A3A2A1A0 000001 */
    PCA9685_ADDRESS_A000010 = 0x02,        /**< A5A4A3A2A1A0 000010 */
    PCA9685_ADDRESS_A000011 = 0x03,        /**< A5A4A3A2A1A0 000011 */
    PCA9685_ADDRESS_A000100 = 0x04,        /**< A5A4A3A2A1A0 000100 */
    PCA9685_ADDRESS_A000101 = 0x05,        /**< A5A4A3A2A1A0 000101 */
    PCA9685_ADDRESS_A000110 = 0x06,        /**< A5A4A3A2A1A0 000110 */
    PCA9685_ADDRESS_A000111 = 0x07,        /**< A5A4A3A2A1A0 000111 */
    PCA9685_ADDRESS_A001000 = 0x08,        /**< A5A4A3A2A1A0 001000 */
    PCA9685_ADDRESS_A001001 = 0x09,        /**< A5A4A3A2A1A0 001001 */
    PCA9685_ADDRESS_A001010 = 0x0A,        /**< A5A4A3A2A1A0 001010 */
    PCA9685_ADDRESS_A001011 = 0x0B,        /**< A5A4A3A2A1A0 001011 */
    PCA9685_ADDRESS_A001100 = 0x0C,        /**< A5A4A3A2A1A0 001100 */
    PCA9685_ADDRESS_A001101 = 0x0D,        /**< A5A4A3A2A1A0 001101 */
    PCA9685_ADDRESS_A001110 = 0x0E,        /**< A5A4A3A2A1A0 001110 */
    PCA9685_ADDRESS_A001111 = 0x0F,        /**< A5A4A3A2A1A0 001111 */
    PCA9685_ADDRESS_A010000 = 0x10,        /**< A5A4A3A2A1A0 010000 */
    PCA9685_ADDRESS_A010001 = 0x11,        /**< A5A4A3A2A1A0 010001 */
    PCA9685_ADDRESS_A010010 = 0x12,        /**< A5A4A3A2A1A0 010010 */
    PCA9685_ADDRESS_A010011 = 0x13,        /**< A5A4A3A2A1A0 010011 */
    PCA9685_ADDRESS_A010100 = 0x14,        /**< A5A4A3A2A1A0 010100 */
    PCA9685_ADDRESS_A010101 = 0x15,        /**< A5A4A3A2A1A0 010101 */
    PCA9685_ADDRESS_A010110 = 0x16,        /**< A5A4A3A2A1A0 010110 */
    PCA9685_ADDRESS_A010111 = 0x17,        /**< A5A4A3A2A1A0 010111 */
    PCA9685_ADDRESS_A011000 = 0x18,        /**< A5A4A3A2A1A0 011000 */
    PCA9685_ADDRESS_A011001 = 0x19,        /**< A5A4A3A2A1A0 011001 */
    PCA9685_ADDRESS_A011010 = 0x1A,        /**< A5A4A3A2A1A0 011010 */
    PCA9685_ADDRESS_A011011 = 0x1B,        /**< A5A4A3A2A1A0 011011 */
    PCA9685_ADDRESS_A011100 = 0x1C,        /**< A5A4A3A2A1A0 011100 */
    PCA9685_ADDRESS_A011101 = 0x1D,        /**< A5A4A3A2A1A0 011101 */
    PCA9685_ADDRESS_A011110 = 0x1E,        /**< A5A4A3A2A1A0 011110 */
    PCA9685_ADDRESS_A011111 = 0x1F,        /**< A5A4A3A2A1A0 011111 */
    PCA9685_ADDRESS_A100000 = 0x20,        /**< A5A4A3A2A1A0 100000 */
    PCA9685_ADDRESS_A100001 = 0x21,        /**< A5A4A3A2A1A0 100001 */
    PCA9685_ADDRESS_A100010 = 0x22,        /**< A5A4A3A2A1A0 100010 */
    PCA9685_ADDRESS_A100011 = 0x23,        /**< A5A4A3A2A1A0 100011 */
    PCA9685_ADDRESS_A100100 = 0x24,        /**< A5A4A3A2A1A0 100100 */
    PCA9685_ADDRESS_A100101 = 0x25,        /**< A5A4A3A2A1A0 100101 */
    PCA9685_ADDRESS_A100110 = 0x26,        /**< A5A4A3A2A1A0 100110 */
    PCA9685_ADDRESS_A100111 = 0x27,        /**< A5A4A3A2A1A0 100111 */
    PCA9685_ADDRESS_A101000 = 0x28,        /**< A5A4A3A2A1A0 101000 */
    PCA9685_ADDRESS_A101001 = 0x29,        /**< A5A4A3A2A1A0 101001 */
    PCA9685_ADDRESS_A101010 = 0x2A,        /**< A5A4A3A2A1A0 101010 */
    PCA9685_ADDRESS_A101011 = 0x2B,        /**< A5A4A3A2A1A0 101011 */
    PCA9685_ADDRESS_A101100 = 0x2C,        /**< A5A4A3A2A1A0 101100 */
    PCA9685_ADDRESS_A101101 = 0x2D,        /**< A5A4A3A2A1A0 101101 */
    PCA9685_ADDRESS_A101110 = 0x2E,        /**< A5A4A3A2A1A0 101110 */
    PCA9685_ADDRESS_A101111 = 0x2F,        /**< A5A4A3A2A1A0 101111 */
    PCA9685_ADDRESS_A110000 = 0x30,        /**< A5A4A3A2A1A0 110000 */
    PCA9685_ADDRESS_A110001 = 0x31,        /**< A5A4A3A2A1A0 110001 */
    PCA9685_ADDRESS_A110010 = 0x32,        /**< A5A4A3A2A1A0 110010 */
    PCA9685_ADDRESS_A110011 = 0x33,        /**< A5A4A3A2A1A0 110011 */
    PCA9685_ADDRESS_A110100 = 0x34,        /**< A5A4A3A2A1A0 110100 */
    PCA9685_ADDRESS_A110101 = 0x35,        /**< A5A4A3A2A1A0 110101 */
    PCA9685_ADDRESS_A110110 = 0x36,        /**< A5A4A3A2A1A0 110110 */
    PCA9685_ADDRESS_A110111 = 0x37,        /**< A5A4A3A2A1A0 110111 */
    PCA9685_ADDRESS_A111000 = 0x38,        /**< A5A4A3A2A1A0 111000 */
    PCA9685_ADDRESS_A111001 = 0x39,        /**< A5A4A3A2A1A0 111001 */
    PCA9685_ADDRESS_A111010 = 0x3A,        /**< A5A4A3A2A1A0 111010 */
    PCA9685_ADDRESS_A111011 = 0x3B,        /**< A5A4A3A2A1A0 111011 */
    PCA9685_ADDRESS_A111100 = 0x3C,        /**< A5A4A3A2A1A0 111100 */
    PCA9685_ADDRESS_A111101 = 0x3D,        /**< A5A4A3A2A1A0 111101 */
    PCA9685_ADDRESS_A111110 = 0x3E,        /**< A5A4A3A2A1A0 111110 */
    PCA9685_ADDRESS_A111111 = 0x3F,        /**< A5A4A3A2A1A0 111111 */
} pca9685_address_t;

/**
 * @brief pca9685 bool enumeration definition
 */
typedef enum
{
    PCA9685_BOOL_FALSE = 0x00,        /**< disable */
    PCA9685_BOOL_TRUE  = 0x01,        /**< enable */
} pca9685_bool_t;

/**
 * @brief pca9685 output change enumeration definition
 */
typedef enum
{
    PCA9685_OUTPUT_CHANGE_STOP = 0x00,        /**< outputs change on stop command */
    PCA9685_OUTPUT_CHANGE_ACK  = 0x01,        /**< outputs change on ack */
} pca9685_output_change_t;

/**
 * @brief pca9685 output driver enumeration definition
 */
typedef enum
{
    PCA9685_OUTPUT_DRIVER_OPEN_DRAIN = 0x00,        /**< outputs are configured with an open drain structure */
    PCA9685_OUTPUT_DRIVER_TOTEM_POLE = 0x01,        /**< outputs are configured with a totem pole structure */
} pca9685_output_driver_t;

/**
 * @brief pca9685 output disable type enumeration definition
 */
typedef enum
{
    PCA9685_OUTPUT_DISABLE_TYPE_LEDN_LOW                                  = 0x00,        /**< when OE = 1 (output drivers not enabled), ledn = 0 */
    PCA9685_OUTPUT_DISABLE_TYPE_OUTDRV_1_LEDN_LOW_OUTDRV_0_HIGH_IMPEDANCE = 0x01,        /**< when OE = 1 (output drivers not enabled), ledn = 1 when OUTDRV = 1
                                                                                              ledn = high impedance when OUTDRV = 0 */
    PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE                            = 0x02,        /**< when OE = 1 (output drivers not enabled), ledn = high impedance */
} pca9685_output_disable_type_t;

/**
 * @brief pca9685 channel enumeration definition
 */
typedef enum
{
    PCA9685_CHANNEL_0  = 0x00,        /**< channel 0 */
    PCA9685_CHANNEL_1  = 0x01,        /**< channel 1 */
    PCA9685_CHANNEL_2  = 0x02,        /**< channel 2 */
    PCA9685_CHANNEL_3  = 0x03,        /**< channel 3 */
    PCA9685_CHANNEL_4  = 0x04,        /**< channel 4 */
    PCA9685_CHANNEL_5  = 0x05,        /**< channel 5 */
    PCA9685_CHANNEL_6  = 0x06,        /**< channel 6 */
    PCA9685_CHANNEL_7  = 0x07,        /**< channel 7 */
    PCA9685_CHANNEL_8  = 0x08,        /**< channel 8 */
    PCA9685_CHANNEL_9  = 0x09,        /**< channel 9 */
    PCA9685_CHANNEL_10 = 0x0A,        /**< channel 10 */
    PCA9685_CHANNEL_11 = 0x0B,        /**< channel 11 */
    PCA9685_CHANNEL_12 = 0x0C,        /**< channel 12 */
    PCA9685_CHANNEL_13 = 0x0D,        /**< channel 13 */
    PCA9685_CHANNEL_14 = 0x0E,        /**< channel 14 */
    PCA9685_CHANNEL_15 = 0x0F,        /**< channel 15 */
} pca9685_channel_t;

/**
 * @brief pca9685 handle structure definition
 */
typedef struct pca9685_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    uint8_t (*oe_gpio_init)(void);                                                      /**< point to an oe_gpio_init function address */
    uint8_t (*oe_gpio_deinit)(void);                                                    /**< point to an oe_gpio_deinit function address */
    uint8_t (*oe_gpio_write)(uint8_t value);                                            /**< point to an oe_gpio_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} pca9685_handle_t;

/**
 * @brief pca9685 information structure definition
 */
typedef struct pca9685_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} pca9685_info_t;

/**
 * @}
 */

/**
 * @defgroup pca9685_link_driver pca9685 link driver function
 * @brief    pca9685 link driver modules
 * @ingroup  pca9685_driver
 * @{
 */

/**
 * @brief     initialize pca9685_handle_t structure
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] STRUCTURE is pca9685l_handle_t
 * @note      none
 */
#define DRIVER_PCA9685_LINK_INIT(HANDLE, STRUCTURE)         memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_IIC_INIT(HANDLE, FUC)           (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_IIC_DEINIT(HANDLE, FUC)         (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_IIC_READ(HANDLE, FUC)           (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_IIC_WEITE(HANDLE, FUC)          (HANDLE)->iic_write = FUC

/**
 * @brief     link oe_gpio_init function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an oe_gpio_init function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_OE_GPIO_INIT(HANDLE, FUC)       (HANDLE)->oe_gpio_init = FUC

/**
 * @brief     link oe_gpio_deinit function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an oe_gpio_deinit function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_OE_GPIO_DEINIT(HANDLE, FUC)     (HANDLE)->oe_gpio_deinit = FUC

/**
 * @brief     link oe_gpio_write function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to an oe_gpio_write function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_OE_GPIO_WRITE(HANDLE, FUC)      (HANDLE)->oe_gpio_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_DELAY_MS(HANDLE, FUC)           (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a pca9685 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_PCA9685_LINK_DEBUG_PRINT(HANDLE, FUC)        (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup pca9685_base_driver pca9685 base driver function
 * @brief    pca9685 base driver modules
 * @ingroup  pca9685_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a pca9685 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9685_info(pca9685_info_t *info);

/**
 * @brief     set the address pin
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] addr_pin is the chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pca9685_set_addr_pin(pca9685_handle_t *handle, pca9685_address_t addr_pin);

/**
 * @brief      get the address pin
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *addr_pin points to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9685_get_addr_pin(pca9685_handle_t *handle, pca9685_address_t *addr_pin);

/**
 * @brief     set the address
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] addr is the chip address
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pca9685_set_addr(pca9685_handle_t *handle, uint8_t addr);

/**
 * @brief      get the address
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *addr points to a chip address buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9685_get_addr(pca9685_handle_t *handle, uint8_t *addr);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a pca9685 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t pca9685_init(pca9685_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a pca9685 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 iic or gpio deinit failed
 * @note      none
 */
uint8_t pca9685_deinit(pca9685_handle_t *handle);

/**
 * @brief     write led channels
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] channel is the led channel
 * @param[in] on_count is the led on count
 * @param[in] off_count is the led off count
 * @return    status code
 *            - 0 success
 *            - 1 write channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 on_count or off_count is over 4096
 * @note      on_count <= 4096 && off_count <= 4096
 */
uint8_t pca9685_write_channel(pca9685_handle_t *handle, pca9685_channel_t channel, uint16_t on_count, uint16_t off_count);

/**
 * @brief      read led channels
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[in]  channel is the led channel
 * @param[out] *on_count points to an led on count buffer
 * @param[out] *off_count points to an led off count buffer
 * @return     status code
 *             - 0 success
 *             - 1 read channel failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_read_channel(pca9685_handle_t *handle, pca9685_channel_t channel, uint16_t *on_count, uint16_t *off_count);

/**
 * @brief     write all led channels
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] on_count is the led on count
 * @param[in] off_count is the led off count
 * @return    status code
 *            - 0 success
 *            - 1 write all channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 on_count or off_count is over 4096
 * @note      on_count <= 4096 && off_count <= 4096
 */
uint8_t pca9685_write_all_channel(pca9685_handle_t *handle, uint16_t on_count, uint16_t off_count);

/**
 * @brief      convert the pwm to the register raw data
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[in]  delay_percent is the start delay percent
 * @param[in]  high_duty_cycle_percent is the pwm high duty cycle percent
 * @param[out] *on_count points to an on counter buffer
 * @param[out] *off_count points to an off counter buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 delay_percent + high_duty_cycle_percent can't be over 100.0
 * @note       0.0 <= delay_percent + high_duty_cycle_percent <= 100.0
 *             0.0 <= delay_percent <= 100.0
 *             0.0 <= high_duty_cycle_percent <= 100.0
 */
uint8_t pca9685_pwm_convert_to_register(pca9685_handle_t *handle, float delay_percent, float high_duty_cycle_percent,
                                        uint16_t *on_count, uint16_t *off_count);

/**
 * @brief      convert the register raw data to the pwm
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[in]  on_count is the led on count
 * @param[in]  off_count is the led off count
 * @param[out] *delay_percent points to a delay percent buffer
 * @param[out] *high_duty_cycle_percent points to a high duty cycle percent buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 on_count or off_count is over 4096
 * @note       on_count <= 4096 && off_count <= 4096
 */
uint8_t pca9685_pwm_convert_to_data(pca9685_handle_t *handle, uint16_t on_count, uint16_t off_count,
                                    float *delay_percent, float *high_duty_cycle_percent);

/**
 * @brief     set the chip active
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set active failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_active(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief     set the clock pres cale
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] prescaler is the clock pre scale
 * @return    status code
 *            - 0 success
 *            - 1 set pre scale failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 prescaler must be >= 3
 * @note      prescaler >= 3
 */
uint8_t pca9685_set_prescaler(pca9685_handle_t *handle, uint8_t prescaler);

/**
 * @brief      get the clock pre scale
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *prescaler points to a clock pre scale buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pre scale failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_prescaler(pca9685_handle_t *handle, uint8_t *prescaler);

/**
 * @brief      convert the output frequency to the register raw data
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[in]  oscillator is the oscillator frequency
 * @param[in]  output_freq is the output frequency
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_output_frequency_convert_to_register(pca9685_handle_t *handle, uint32_t oscillator, uint16_t output_freq, uint8_t *reg);

/**
 * @brief      convert the register raw data to the output frequency
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[in]  oscillator is the oscillator frequency
 * @param[in]  reg is the register raw data
 * @param[out] *output_freq points to an output frequency buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_output_frequency_convert_to_data(pca9685_handle_t *handle, uint32_t oscillator, uint8_t reg, uint16_t *output_freq);

/**
 * @brief     enable or disable restart
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set restart failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_restart(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the restart status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get restart failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_restart(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable the external clock pin
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set external clock pin failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_external_clock_pin(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the external clock pin status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get external clock pin failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_external_clock_pin(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable the register auto increment
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set register auto increment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_register_auto_increment(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the register auto increment status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get register auto increment failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_register_auto_increment(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable the sleep mode
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_sleep_mode(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the sleep mode status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_sleep_mode(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable respond sub address 1
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond sub address 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_subaddress_1(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the respond sub address 1 status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond sub address 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_subaddress_1(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable respond sub address 2
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond sub address 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_subaddress_2(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the respond sub address 2 status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond sub address 2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_subaddress_2(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable respond sub address 3
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond sub address 3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_subaddress_3(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the respond sub address 3 status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond sub address 3 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_subaddress_3(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable respond all call
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond all call failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_all_call(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the respond all call status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond all call failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_all_call(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     enable or disable output invert
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set output invert failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_invert(pca9685_handle_t *handle, pca9685_bool_t enable);

/**
 * @brief      get the output invert status
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output invert failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_invert(pca9685_handle_t *handle, pca9685_bool_t *enable);

/**
 * @brief     set the output change type
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] change is the output change type
 * @return    status code
 *            - 0 success
 *            - 1 set output change failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_change(pca9685_handle_t *handle, pca9685_output_change_t change);

/**
 * @brief      get the output change type
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *change points to an output change type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output change failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_change(pca9685_handle_t *handle, pca9685_output_change_t *change);

/**
 * @brief     set the output driver type
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] driver is the output driver type
 * @return    status code
 *            - 0 success
 *            - 1 set output driver failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_driver(pca9685_handle_t *handle, pca9685_output_driver_t driver);

/**
 * @brief      get the output driver type
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *driver points to an output driver type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output driver failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_driver(pca9685_handle_t *handle, pca9685_output_driver_t *driver);

/**
 * @brief     set the output disable type
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] type is the output disable type
 * @return    status code
 *            - 0 success
 *            - 1 set output disable type failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_disable_type(pca9685_handle_t *handle, pca9685_output_disable_type_t type);

/**
 * @brief      get the output disable type
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *type points to an output disable type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output disable type failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_disable_type(pca9685_handle_t *handle, pca9685_output_disable_type_t *type);

/**
 * @brief     set the sub address 1
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] addr is the sub address 1
 * @return    status code
 *            - 0 success
 *            - 1 set sub address 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_subaddress_1(pca9685_handle_t *handle, uint8_t addr);

/**
 * @brief      get the sub address 1
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *addr points to a sub address 1 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub address 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_subaddress_1(pca9685_handle_t *handle, uint8_t *addr);

/**
 * @brief     set the sub address 2
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] addr is the sub address 2
 * @return    status code
 *            - 0 success
 *            - 1 set sub address 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_subaddress_2(pca9685_handle_t *handle, uint8_t addr);

/**
 * @brief      get the sub address 2
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *addr points to a sub address 2 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub address 2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_subaddress_2(pca9685_handle_t *handle, uint8_t *addr);

/**
 * @brief     set the sub address 3
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] addr is the sub address 3
 * @return    status code
 *            - 0 success
 *            - 1 set sub address 3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_subaddress_3(pca9685_handle_t *handle, uint8_t addr);

/**
 * @brief      get the sub address 3
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *addr points to a sub address 3 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub address 3 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_subaddress_3(pca9685_handle_t *handle, uint8_t *addr);

/**
 * @brief     set the all call address
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] addr is the all call address
 * @return    status code
 *            - 0 success
 *            - 1 set all call address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_all_call_address(pca9685_handle_t *handle, uint8_t addr);

/**
 * @brief      set the all call address
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[out] *addr points to an all call address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get all call address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_all_call_address(pca9685_handle_t *handle, uint8_t *addr);

/**
 * @}
 */

/**
 * @defgroup pca9685_extend_driver pca9685 extend driver function
 * @brief    pca9685 extend driver modules
 * @ingroup  pca9685_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a pca9685 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_reg(pca9685_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a pca9685 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_reg(pca9685_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
