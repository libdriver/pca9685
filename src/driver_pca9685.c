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
 * @file      driver_pca9685.c
 * @brief     driver pca9685 source file
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

#include "driver_pca9685.h"
#include <math.h>

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP PCA9685"        /**< chip name */
#define MANUFACTURER_NAME         "NXP"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.3f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                 /**< chip max supply voltage */
#define MAX_CURRENT               400.0f               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief chip register definition
 */
#define PCA9685_REG_MODE1                 0x00        /**< mode register 1 */
#define PCA9685_REG_MODE2                 0x01        /**< mode register 2 */
#define PCA9685_REG_SUBADR1               0x02        /**< iic bus sub address 1 */
#define PCA9685_REG_SUBADR2               0x03        /**< iic bus sub address 2 */
#define PCA9685_REG_SUBADR3               0x04        /**< iic bus sub address 3 */
#define PCA9685_REG_ALLCALLADR            0x05        /**< led all call iic bus address */
#define PCA9685_REG_LED0_ON_L             0x06        /**< led0 output and brightness control byte 0 */
#define PCA9685_REG_LED0_ON_H             0x07        /**< led0 output and brightness control byte 1 */
#define PCA9685_REG_LED0_OFF_L            0x08        /**< led0 output and brightness control byte 2 */
#define PCA9685_REG_LED0_OFF_H            0x09        /**< led0 output and brightness control byte 3 */
#define PCA9685_REG_ALL_LED_ON_L          0xFA        /**< load all the led_on registers byte 0 */
#define PCA9685_REG_ALL_LED_ON_H          0xFB        /**< load all the led_on registers byte 1 */
#define PCA9685_REG_ALL_LED_OFF_L         0xFC        /**< load all the led_off registers byte 0 */
#define PCA9685_REG_ALL_LED_OFF_H         0xFD        /**< load all the led_off registers byte 1 */
#define PCA9685_REG_PRE_SCALE             0xFE        /**< pre scale for pwm output frequency */

/**
 * @brief     set the address pin
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] addr_pin chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pca9685_set_addr_pin(pca9685_handle_t *handle, pca9685_address_t addr_pin)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }

    handle->iic_addr = 0x80;                  /* set 0x80*/
    handle->iic_addr |= addr_pin << 1;        /* set iic addr */

    return 0;                                 /* success return 0 */
}

/**
 * @brief      get the address pin
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *addr_pin pointer to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9685_get_addr_pin(pca9685_handle_t *handle, pca9685_address_t *addr_pin)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }

    *addr_pin = (pca9685_address_t)((handle->iic_addr & (~0x80)) >> 1);        /*get iic address */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set the address
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] addr chip address
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pca9685_set_addr(pca9685_handle_t *handle, uint8_t addr)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }

    handle->iic_addr = addr;        /* set iic addr */

    return 0;                       /* success return 0 */
}

/**
 * @brief      get the address
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *addr pointer to a chip address buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9685_get_addr(pca9685_handle_t *handle, uint8_t *addr)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }

    *addr = handle->iic_addr;       /* get iic addr */

    return 0;                       /* success return 0 */
}

/**
 * @brief     set the chip active
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set active failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_active(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }

    if (handle->oe_gpio_write(!enable) != 0)                         /* gpio write */
    {
        handle->debug_print("pcf8591: gpio write failed.\n");        /* gpio writer failed */

        return 1;                                                    /* return error */
    }

    return 0;                                                        /* success return 0 */
}

/**
 * @brief     enable or disable restart
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set restart failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_restart(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 7);                                                                       /* clear conf */
    prev |= enable << 7;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the restart status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get restart failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_restart(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 7) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable the external clock pin
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set external clock pin failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_external_clock_pin(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 6);                                                                       /* clear conf */
    prev |= enable << 6;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the external clock pin status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get external clock pin failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_external_clock_pin(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 6) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable the register auto increment
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set register auto increment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_register_auto_increment(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 5);                                                                       /* clear conf */
    prev |= enable << 5;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the register auto increment status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get register auto increment failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_register_auto_increment(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 5) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable the sleep mode
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_sleep_mode(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 4);                                                                       /* clear conf */
    prev |= enable << 4;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the sleep mode status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_sleep_mode(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 4) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable respond sub address 1
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond sub address 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_subaddress_1(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 3);                                                                       /* clear conf */
    prev |= enable << 3;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the respond sub address 1 status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond sub address 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_subaddress_1(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 3) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable respond sub address 2
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond sub address 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_subaddress_2(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 2);                                                                       /* clear conf */
    prev |= enable << 2;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the respond sub address 2 status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond sub address 2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_subaddress_2(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 2) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable respond sub address 3
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond sub address 3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_subaddress_3(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 1);                                                                       /* clear conf */
    prev |= enable << 1;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the respond sub address 3 status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond sub address 3 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_subaddress_3(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 1) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable respond all call
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set respond all call failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_respond_all_call(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 0);                                                                       /* clear conf */
    prev |= enable << 0;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);       /* write mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                     /* write mode 1 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the respond all call status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get respond all call failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_respond_all_call(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* read mode 1 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                      /* read mode 1 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 0) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     enable or disable output invert
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set output invert failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_invert(pca9685_handle_t *handle, pca9685_bool_t enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 4);                                                                       /* clear conf */
    prev |= enable << 4;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);       /* write mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 2 register failed.\n");                     /* write mode 2 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the output invert status
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output invert failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_invert(pca9685_handle_t *handle, pca9685_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    *enable = (pca9685_bool_t)((prev >> 4) & 0x01);                                          /* get bool */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     set the output change type
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] change output change type
 * @return    status code
 *            - 0 success
 *            - 1 set output change failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_change(pca9685_handle_t *handle, pca9685_output_change_t change)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 3);                                                                       /* clear conf */
    prev |= change << 3;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);       /* write mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 2 register failed.\n");                     /* write mode 2 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the output change type
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *change pointer to an output change type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output change failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_change(pca9685_handle_t *handle, pca9685_output_change_t *change)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    *change = (pca9685_output_change_t)((prev >> 3) & 0x01);                                 /* get change */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     set the output driver type
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] driver output driver type
 * @return    status code
 *            - 0 success
 *            - 1 set output driver failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_driver(pca9685_handle_t *handle, pca9685_output_driver_t driver)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(1 << 2);                                                                       /* clear conf */
    prev |= driver << 2;                                                                     /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);       /* write mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 2 register failed.\n");                     /* write mode 2 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the output driver type
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *driver pointer to an output driver type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output driver failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_driver(pca9685_handle_t *handle, pca9685_output_driver_t *driver)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    *driver = (pca9685_output_driver_t)((prev >> 2) & 0x01);                                 /* get change */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     set the output disable type
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] type output disable type
 * @return    status code
 *            - 0 success
 *            - 1 set output disable type failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_output_disable_type(pca9685_handle_t *handle, pca9685_output_disable_type_t type)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    prev &= ~(3 << 0);                                                                       /* clear conf */
    prev |= type << 0;                                                                       /* set conf */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);       /* write mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: write mode 2 register failed.\n");                     /* write mode 2 register failed */

        return 1;                                                                            /* return error */
    }

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      get the output disable type
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *type pointer to an output disable type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output disable type failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_output_disable_type(pca9685_handle_t *handle, pca9685_output_disable_type_t *type)
{
    uint8_t res;
    uint8_t prev;

    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE2, (uint8_t *)&prev, 1);        /* read mode 2 register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read mode 2 register failed.\n");                      /* read mode 2 register failed */

        return 1;                                                                            /* return error */
    }
    *type = (pca9685_output_disable_type_t)((prev >> 0) & (0x3));                            /* get type */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     set the sub address 1
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] addr sub address 1
 * @return    status code
 *            - 0 success
 *            - 1 set sub address 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_subaddress_1(pca9685_handle_t *handle, uint8_t addr)
{
    uint8_t res;

    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }

    res = handle->iic_write(handle->iic_addr, PCA9685_REG_SUBADR1, (uint8_t *)&addr, 1);        /* write sub address 1 register */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pcf8591: write sub address 1 register failed.\n");                 /* write sub address 1 register failed */

        return 1;                                                                               /* return error */
    }

    return 0;                                                                                   /* success return 0 */
}

/**
 * @brief      get the sub address 1
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *addr pointer to a sub address 1 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub address 1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_subaddress_1(pca9685_handle_t *handle, uint8_t *addr)
{
    uint8_t res;

    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_SUBADR1, (uint8_t *)addr, 1);        /* read sub address 1 register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("pcf8591: read sub address 1 register failed.\n");                /* read sub address 1 register failed */

        return 1;                                                                             /* return error */
    }

    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief     set the sub address 2
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] addr sub address 2
 * @return    status code
 *            - 0 success
 *            - 1 set sub address 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_subaddress_2(pca9685_handle_t *handle, uint8_t addr)
{
    uint8_t res;

    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }

    res = handle->iic_write(handle->iic_addr, PCA9685_REG_SUBADR2, (uint8_t *)&addr, 1);        /* write sub address 2 register */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pcf8591: write sub address 2 register failed.\n");                 /* write sub address 2 register failed */

        return 1;                                                                               /* return error */
    }

    return 0;                                                                                   /* success return 0 */
}

/**
 * @brief      get the sub address 2
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *addr pointer to a sub address 2 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub address 2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_subaddress_2(pca9685_handle_t *handle, uint8_t *addr)
{
    uint8_t res;

    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_SUBADR2, (uint8_t *)addr, 1);        /* read sub address 2 register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("pcf8591: read sub address 2 register failed.\n");                /* read sub address 2 register failed */

        return 1;                                                                             /* return error */
    }

    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief     set the sub address 3
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] addr sub address 3
 * @return    status code
 *            - 0 success
 *            - 1 set sub address 3 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_subaddress_3(pca9685_handle_t *handle, uint8_t addr)
{
    uint8_t res;

    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }

    res = handle->iic_write(handle->iic_addr, PCA9685_REG_SUBADR3, (uint8_t *)&addr, 1);        /* write sub address 3 register */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pcf8591: write sub address 3 register failed.\n");                 /* write sub address 3 register failed */

        return 1;                                                                               /* return error */
    }

    return 0;                                                                                   /* success return 0 */
}

/**
 * @brief      get the sub address 3
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *addr pointer to a sub address 3 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub address 3 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_subaddress_3(pca9685_handle_t *handle, uint8_t *addr)
{
    uint8_t res;

    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_SUBADR3, (uint8_t *)addr, 1);        /* read sub address 3 register */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("pcf8591: read sub address 3 register failed.\n");                /* read sub address 3 register failed */

        return 1;                                                                             /* return error */
    }

    return 0;                                                                                 /* success return 0 */
}

/**
 * @brief     set the all call address
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] addr all call address
 * @return    status code
 *            - 0 success
 *            - 1 set all call address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_all_call_address(pca9685_handle_t *handle, uint8_t addr)
{
    uint8_t res;

    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }

    res = handle->iic_write(handle->iic_addr, PCA9685_REG_ALLCALLADR, (uint8_t *)&addr, 1);        /* write all call address register */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("pcf8591: write all call address register failed.\n");                 /* write all call address register failed */

        return 1;                                                                                  /* return error */
    }

    return 0;                                                                                      /* success return 0 */
}

/**
 * @brief      set the all call address
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *addr pointer to an all call address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get all call address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_all_call_address(pca9685_handle_t *handle, uint8_t *addr)
{
    uint8_t res;

    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_ALLCALLADR, (uint8_t *)addr, 1);        /* read all call address register */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("pcf8591: read all call address register failed.\n");                /* read all call address register failed */

        return 1;                                                                                /* return error */
    }

    return 0;                                                                                    /* success return 0 */
}

/**
 * @brief     write led channels
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] channel led channel
 * @param[in] on_count led on count
 * @param[in] off_count led off count
 * @return    status code
 *            - 0 success
 *            - 1 write channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 on_count or off_count is over 4096
 * @note      on_count <= 4096 && off_count <= 4096
 */
uint8_t pca9685_write_channel(pca9685_handle_t *handle, pca9685_channel_t channel, uint16_t on_count, uint16_t off_count)
{
    uint8_t res;
    uint8_t buf[4];

    if (handle == NULL)                                                                                       /* check handle */
    {
        return 2;                                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                                  /* check handle initialization */
    {
        return 3;                                                                                             /* return error */
    }
    if ((on_count > 4096) || (off_count > 4096))                                                              /* check result */
    {
        handle->debug_print("pcf8591: on_count or off_count is over 4096.\n");                                /* on_count or off_count is over 4096 */

        return 4;                                                                                             /* return error */
    }

    buf[0] = (on_count >> 0) & 0xFF;                                                                          /* set off count lsb */
    buf[1] = (on_count >> 8) & 0x1F;                                                                          /* set on count msb */
    buf[2] = (off_count >> 0) & 0xFF;                                                                         /* set off count lsb */
    buf[3] = (off_count >> 8) & 0x1F;                                                                         /* set off count msb */
    res = handle->iic_write(handle->iic_addr, (uint8_t)(PCA9685_REG_LED0_ON_L + channel * 4),
                           (uint8_t *)buf, 4);                                                                /* write led register */
    if (res != 0)                                                                                             /* check result */
    {
        handle->debug_print("pcf8591: write led register failed.\n");                                         /* write led register failed */

        return 1;                                                                                             /* return error */
    }

    return 0;                                                                                                 /* success return 0 */
}

/**
 * @brief      read led channels
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[in]  channel led channel
 * @param[out] *on_count pointer to an led on count buffer
 * @param[out] *off_count pointer to an led off count buffer
 * @return     status code
 *             - 0 success
 *             - 1 read channel failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_read_channel(pca9685_handle_t *handle, pca9685_channel_t channel, uint16_t *on_count, uint16_t *off_count)
{
    uint8_t res;
    uint8_t buf[4];

    if (handle == NULL)                                                                                      /* check handle */
    {
        return 2;                                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                                 /* check handle initialization */
    {
        return 3;                                                                                            /* return error */
    }

    memset(buf, 0, sizeof(uint8_t) * 4);                                                                     /* clear the buffer */
    res = handle->iic_read(handle->iic_addr, (uint8_t)(PCA9685_REG_LED0_ON_L + channel * 4),
                          (uint8_t *)buf, 4);                                                                /* read led register */
    if (res != 0)                                                                                            /* check result */
    {
        handle->debug_print("pcf8591: read led register failed.\n");                                         /* read led register failed */

        return 1;                                                                                            /* return error */
    }
    *on_count = ((uint16_t)(buf[1]) & 0x1F) << 8 | buf[0];                                                   /* set on count */
    *off_count = ((uint16_t)(buf[3]) & 0x1F) << 8 | buf[2];                                                  /* set off count */

    return 0;                                                                                                /* success return 0 */
}

/**
 * @brief     write all led channels
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] on_count led on count
 * @param[in] off_count led off count
 * @return    status code
 *            - 0 success
 *            - 1 write all channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 on_count or off_count is over 4096
 * @note      on_count <= 4096 && off_count <= 4096
 */
uint8_t pca9685_write_all_channel(pca9685_handle_t *handle, uint16_t on_count, uint16_t off_count)
{
    uint8_t res;
    uint8_t buf[4];

    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }
    if ((on_count > 4096) || (off_count > 4096))                                                   /* check result */
    {
        handle->debug_print("pcf8591: on_count or off_count is over 4096.\n");                     /* on_count or off_count is over 4096 */

        return 4;                                                                                  /* return error */
    }

    buf[0] = (on_count >> 0) & 0xFF;                                                               /* set off count lsb */
    buf[1] = (on_count >> 8) & 0x1F;                                                               /* set on count msb */
    buf[2] = (off_count >> 0) & 0xFF;                                                              /* set off count lsb */
    buf[3] = (off_count >> 8) & 0x1F;                                                              /* set off count msb */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_ALL_LED_ON_L, (uint8_t *)buf, 4);        /* write all led register */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("pcf8591: write all led register failed.\n");                          /* write all led register failed */

        return 1;                                                                                  /* return error */
    }

    return 0;                                                                                      /* success return 0 */
}

/**
 * @brief     set the clock pres cale
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] prescaler clock pre scale
 * @return    status code
 *            - 0 success
 *            - 1 set pre scale failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 prescaler must be >= 3
 * @note      prescaler >= 3
 */
uint8_t pca9685_set_prescaler(pca9685_handle_t *handle, uint8_t prescaler)
{
    uint8_t res;

    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    if (prescaler < 3)                                                                                 /* check result */
    {
        handle->debug_print("pcf8591: pre scale must be >= 3.\n");                                     /* pre scale must be >= 3 */

        return 4;                                                                                      /* return error */
    }

    res = handle->iic_write(handle->iic_addr, PCA9685_REG_PRE_SCALE, (uint8_t *)&prescaler, 1);        /* write pre scale register */
    if (res != 0)                                                                                      /* check result */
    {
        handle->debug_print("pcf8591: write pre scale register failed.\n");                            /* write pre scale register failed */

        return 1;                                                                                      /* return error */
    }

    return 0;                                                                                          /* success return 0 */
}

/**
 * @brief      get the clock pre scale
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[out] *prescaler pointer to a clock pre scale buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pre scale failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_prescaler(pca9685_handle_t *handle, uint8_t *prescaler)
{
    uint8_t res;

    if (handle == NULL)                                                                              /* check handle */
    {
        return 2;                                                                                    /* return error */
    }
    if (handle->inited != 1)                                                                         /* check handle initialization */
    {
        return 3;                                                                                    /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_PRE_SCALE, (uint8_t *)prescaler, 1);        /* read pre scale register */
    if (res != 0)                                                                                    /* check result */
    {
        handle->debug_print("pcf8591: read pre scale register failed.\n");                           /* read pre scale register failed */

        return 1;                                                                                    /* return error */
    }

    return 0;                                                                                        /* success return 0 */
}

/**
 * @brief      convert the output frequency to the register raw data
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[in]  oscillator oscillator frequency
 * @param[in]  output_freq output frequency
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_output_frequency_convert_to_register(pca9685_handle_t *handle, uint32_t oscillator, uint16_t output_freq, uint8_t *reg)
{
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }

    *reg = (uint8_t)(round((double)oscillator / ((double)output_freq * 4096.0))) - 1;        /* convert real data to register data */

    return 0;                                                                                /* success return 0 */
}

/**
 * @brief      convert the register raw data to the output frequency
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[in]  oscillator oscillator frequency
 * @param[in]  reg register raw data
 * @param[out] *output_freq pointer to an output frequency buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_output_frequency_convert_to_data(pca9685_handle_t *handle, uint32_t oscillator, uint8_t reg, uint16_t *output_freq)
{
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }

    *output_freq = (uint16_t)(round((double)oscillator / ((reg + 1) * 4096.0)));        /* convert raw data to real data */

    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      convert the pwm to the register raw data
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[in]  delay_percent start delay percent
 * @param[in]  high_duty_cycle_percent pwm high duty cycle percent
 * @param[out] *on_count pointer to an on counter buffer
 * @param[out] *off_count pointer to an off counter buffer
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
                                        uint16_t *on_count, uint16_t *off_count)
{
    if (handle == NULL)                                                                                        /* check handle */
    {
        return 2;                                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                                   /* check handle initialization */
    {
        return 3;                                                                                              /* return error */
    }
    if (delay_percent + high_duty_cycle_percent >=100.0f)                                                      /* check result */
    {
        handle->debug_print("pcf8591: delay_percent + high_duty_cycle_percent can't be over 100.0.\n");        /* delay_percent + high_duty_cycle_percent can't be over 100.0 */

        return 4;                                                                                              /* return error */
    }

    *on_count = (uint16_t)(roundf(delay_percent / 100.0f * 4096.0f));                                          /* set on count */
    *off_count = (uint16_t)(roundf((delay_percent + high_duty_cycle_percent) / 100.0f * 4096.0f));             /* set off count */

    return 0;                                                                                                  /* success return 0 */
}

/**
 * @brief      convert the register raw data to the pwm
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[in]  on_count led on count
 * @param[in]  off_count led off count
 * @param[out] *delay_percent pointer to a delay percent buffer
 * @param[out] *high_duty_cycle_percent pointer to a high duty cycle percent buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 on_count or off_count is over 4096
 * @note       on_count <= 4096 && off_count <= 4096
 */
uint8_t pca9685_pwm_convert_to_data(pca9685_handle_t *handle, uint16_t on_count, uint16_t off_count,
                                    float *delay_percent, float *high_duty_cycle_percent)
{
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    if ((on_count > 4096) || (off_count > 4096))                                        /* check result */
    {
        handle->debug_print("pcf8591: on_count or off_count is over 4096.\n");          /* on_count or off_count is over 4096 */

        return 4;                                                                       /* return error */
    }

    *delay_percent = (float)(on_count) / 4096.0f * 100.0f;                              /* set the delay_percent */
    *high_duty_cycle_percent = (float)(off_count - on_count) / 4096.0f * 100.0f;        /* set the high_duty_cycle_percent */

    return 0;                                                                           /* success return 0 */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a pca9685 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t pca9685_init(pca9685_handle_t *handle)
{
    uint8_t res, prev;

    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->debug_print == NULL)                                                              /* check debug_print */
    {
        return 3;                                                                                 /* return error */
    }
    if (handle->iic_init == NULL)                                                                 /* check iic_init */
    {
        handle->debug_print("pca9685: iic_init is null.\n");                                      /* iic_init is null */

        return 3;                                                                                 /* return error */
    }
    if (handle->iic_deinit == NULL)                                                               /* check iic_deinit */
    {
        handle->debug_print("pca9685: iic_deinit is null.\n");                                    /* iic_deinit is null */

        return 3;                                                                                 /* return error */
    }
    if (handle->iic_read == NULL)                                                                 /* check iic_read */
    {
        handle->debug_print("pca9685: iic_read is null.\n");                                      /* iic_read is null */

        return 3;                                                                                 /* return error */
    }
    if (handle->iic_write == NULL)                                                                /* check iic_write */
    {
        handle->debug_print("pca9685: iic_write is null.\n");                                     /* iic_write is null */

        return 3;                                                                                 /* return error */
    }
    if (handle->oe_gpio_init == NULL)                                                             /* check oe_gpio_init */
    {
        handle->debug_print("pca9685: oe_gpio_init is null.\n");                                  /* oe_gpio_init is null */

        return 3;                                                                                 /* return error */
    }
    if (handle->oe_gpio_deinit == NULL)                                                           /* check oe_gpio_deinit */
    {
        handle->debug_print("pca9685: oe_gpio_deinit is null.\n");                                /* oe_gpio_deinit is null */

        return 3;                                                                                 /* return error */
    }
    if (handle->oe_gpio_write == NULL)                                                            /* check oe_gpio_write */
    {
        handle->debug_print("pca9685: oe_gpio_write is null.\n");                                 /* oe_gpio_write is null */

        return 3;                                                                                 /* return error */
    }

    if (handle->iic_init() != 0)                                                                  /* iic init */
    {
        handle->debug_print("pca9685: iic init failed.\n");                                       /* iic init failed */

        return 1;                                                                                 /* return error */
    }
    if (handle->oe_gpio_init() != 0)                                                              /* oe gpio init */
    {
        handle->debug_print("pca9685: oe gpio init failed.\n");                                   /* oe gpio init failed */
        (void)handle->iic_deinit();                                                               /* iic deinit */

        return 1;                                                                                 /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);             /* read mode 1 register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("pcf8591: read mode 1 register failed.\n");                           /* read mode 1 register failed */
        (void)handle->oe_gpio_deinit();                                                           /* oe gpio deinit */
        (void)handle->iic_deinit();                                                               /* iic deinit */

        return 4;                                                                                 /* return error */
    }
    if ((prev & 0x80) != 0)                                                                       /* check reset bit */
    {
        prev &= ~(1 << 4);                                                                        /* clear sleep bit */
        res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);        /* write mode 1 register */
        if (res != 0)                                                                             /* check result */
        {
            handle->debug_print("pcf8591: write mode 1 register failed.\n");                      /* write mode 1 register failed */
            (void)handle->oe_gpio_deinit();                                                       /* oe gpio deinit */
            (void)handle->iic_deinit();                                                           /* iic deinit */

            return 4;                                                                             /* return error */
        }
        handle->delay_ms(2);                                                                      /* delay 2 ms */
    }
    prev |= (1 << 7);                                                                             /* set reset bit */
    prev &= ~(1 << 6);                                                                            /* clear extern clock bit */
    prev &= ~(1 << 4);                                                                            /* clear sleep bit */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);            /* write mode 1 register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("pcf8591: write mode 1 register failed.\n");                          /* write mode 1 register failed */
        (void)handle->oe_gpio_deinit();                                                           /* oe gpio deinit */
        (void)handle->iic_deinit();                                                               /* iic deinit */

        return 4;                                                                                 /* return error */
    }
    handle->delay_ms(2);                                                                          /* delay 2 ms */
    handle->inited = 1;                                                                           /* flag finish initialization */

    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a pca9685 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 iic or gpio deinit failed
 * @note      none
 */
uint8_t pca9685_deinit(pca9685_handle_t *handle)
{
    uint8_t res, prev;

    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }

    res = handle->iic_read(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);             /* read mode 1 register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("pcf8591: power down failed failed.\n");                              /* power down failed */

        return 1;                                                                                 /* return error */
    }
    prev |= (1 << 4);                                                                             /* set sleep bit */
    res = handle->iic_write(handle->iic_addr, PCA9685_REG_MODE1, (uint8_t *)&prev, 1);            /* write mode 1 register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("pcf8591: power down failed failed.\n");                              /* power down failed */

        return 1;                                                                                 /* return error */
    }
    if (handle->oe_gpio_deinit() != 0)                                                            /* oe gpio deinit */
    {
        handle->debug_print("pcf8591: oe gpio deinit failed.\n");                                 /* oe gpio deinit failed */

        return 4;                                                                                 /* return error */
    }
    if (handle->iic_deinit() != 0)                                                                /* iic deinit */
    {
        handle->debug_print("pcf8591: iic deinit failed.\n");                                     /* iic deinit failed */

        return 4;                                                                                 /* return error */
    }
    handle->inited = 0;                                                                           /* set closed flag */

    return 0;                                                                                     /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a pca9685 handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pca9685_set_reg(pca9685_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }

    if (handle->iic_write(handle->iic_addr, reg, buf, len) != 0)      /* write data */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a pca9685 handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pca9685_get_reg(pca9685_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }

    if (handle->iic_read(handle->iic_addr, reg, buf, len) != 0)      /* read data */
    {
        return 1;                                                    /* return error */
    }
    else
    {
        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a pca9685 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pca9685_info(pca9685_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(pca9685_info_t));                        /* initialize pca9685 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
