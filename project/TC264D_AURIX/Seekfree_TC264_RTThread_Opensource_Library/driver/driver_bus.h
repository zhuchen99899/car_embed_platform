/**
 * @file driver_bus.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-29
 * 
 * 
 */

#ifndef __DRIVER_BUS_H__
#define __DRIVER_BUS_H__

#include <stdint.h>

/**
 * @brief Register an I2C bus driver
 * @param i2c_bus_name Name of the I2C bus to register
 */
void driver_i2c_bus_register(const char *i2c_bus_name);

#endif
