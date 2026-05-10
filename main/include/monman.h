#ifndef NIBBLE_MONMAN_H
#define NIBBLE_MONMAN_H

#include "types.h"
#include "i2cman.h"
#include "device/ssd1306.h"

typedef struct {
	void *data;
	size_t size;
} monman_conf_t;

typedef struct {
	uint8_t **floor_matrix;
	uint8_t **float_matrix;
	size_t len;
	size_t wid;
} monman_matrix_t;

status_t monman_setup(monman_conf_t *conf, monman_matrix_t *mtx);

status_t monman_setdown(monman_matrix_t *mtx);

#endif
