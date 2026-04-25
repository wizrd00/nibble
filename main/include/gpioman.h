#ifndef NIBBLE_GPIOMAN_H
#define NIBBLE_GPIOMAN_H

#include "types.h"
#include "driver/gpio.h"

typedef struct {
	uint32_t pin_mask;
} gpioman_conf_t;

typedef struct {
	uint32_t level;
	gpio_num_t gpio_num;
	gpio_mode_t mode;
	gpio_int_type_t intr_type;
	gpio_isr_t handler;
} gpioman_pin_t;

status_t gpioman_setup(gpioman_conf_t *conf);

status_t gpioman_setdown(void);

status_t gpioman_config_pin(gpioman_pin_t *pin);

status_t gpioman_modify_level(gpioman_pin_t *pin, uint32_t level);

status_t gpioman_modify_handler(gpioman_pin_t *pin, gpio_isr_t handler);

#endif
