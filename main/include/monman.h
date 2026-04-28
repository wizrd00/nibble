#ifndef NIBBLE_MONMAN_H
#define NIBBLE_MONMAN_H

#include "types.h"
#include "i2cman.h"
#include "device/ssd1306.h"

typedef struct {
	uint8_t ratio;
	bool x_remap;
	bool y_remap;
} monman_conf_t;

typedef struct {
	uint8_t **floor_matrix;
	uint8_t **float_matrix;
	size_t lenght;
	size_t width;
} monman_matrix_t;

status_t monman_setup(monman_conf_t *conf, monman_matrix_t *mtx);

status_t monman_setdown();

#endif
