#ifndef NIBBLE_I2CMAN_H
#define NIBBLE_I2CMAN_H

#include "types.h"
#include "driver/i2c.h"

#define I2CMAN_SEND I2C_MASTER_WRITE
#define I2CMAN_RECV I2C_MASTER_READ
#define I2CMAN_PORT I2C_NUM_0
#define I2CMAN_MODE I2C_MODE_MASTER
#define I2CMAN_ACKV I2C_MASTER_LAST_NACK

typedef struct {
	gpio_num_t sda_gpio_num;
	gpio_num_t scl_gpio_num;
	uint32_t clock_tick;
} i2cman_conf_t;

status_t i2cman_setup(i2cman_conf_t *conf);

status_t i2cman_setdown(void);

status_t i2cman_send(int8_t addr, void *data, size_t data_len, bool ack_check, TickType_t timeout);

status_t i2cman_recv(int8_t addr, void *data, size_t data_len, TickType_t timeout);

#endif
