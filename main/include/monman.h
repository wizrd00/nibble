#ifndef NIBBLE_MONMAN_H
#define NIBBLE_MONMAN_H

#include "types.h"
#include "i2cman.h"
#include "driver/ssd1306.h"

typedef struct {
	void *data;
	size_t size;
} monman_conf_t;

status_t monman_setup(monman_conf_t *conf);

status_t monman_setdown(void);

#endif
