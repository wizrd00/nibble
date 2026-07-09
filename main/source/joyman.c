#include "joyman.h"

status_t joyman_joystick_position(int *val)
{
	status_t _stat = NIBBLE_SUCCESS;
	uint16_t tmp_val;
	CHECK_STAT(adcman_measure(&tmp_val), "adcman_measure() failed");
	*val = (int) (tmp_val == JOYSTICK_ORIGIN_LEVEL) ? 0 : (tmp_val < JOYSTICK_ORIGIN_LEVEL) ? PERCENTAGE_UP(tmp_val) : PERCENTAGE_DOWN(tmp_val);
	return _stat;
}

status_t joyman_button_status(gpio_num_t gpio_num, int *val)
{
	status_t _stat = NIBBLE_SUCCESS;
	*val = (gpio_get_level(gpio_num) == JOYSTICK_CLICK_LEVEL) ? 1 : 0;
	return _stat;
}
