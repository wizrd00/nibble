#ifndef NIBBLE_JOYMAN_H
#define NIBBLE_JOYMAN_H

#include "types.h"
#include "adcman.h"
#include "gpioman.h"
#include "device/hw504.h"

#define PERCENTAGE_UP(val) (((JOYSTICK_ORIGIN_LEVEL - (int) tmp_val) * 100) / (JOYSTICK_ORIGIN_LEVEL - JOYSTICK_MIN_LEVEL))
#define PERCENTAGE_DOWN(val) ((((int) tmp_val - JOYSTICK_ORIGIN_LEVEL) * -100) / (JOYSTICK_MAX_LEVEL - JOYSTICK_ORIGIN_LEVEL))

status_t joyman_joystick_position(int *val);

status_t joyman_button_status(gpio_num_t gpio_num, int *val);

#endif
