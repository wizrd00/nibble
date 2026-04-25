#include "gpioman.h"

status_t gpioman_setup(gpioman_conf_t *conf)
{
	status_t _stat = NIBBLE_SUCCESS;
	gpio_config_t tmp_gpio_conf = {
		.pin_bit_mask = conf->pin_mask,
		.mode = GPIO_MODE_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type = GPIO_INTR_DISABLE
	};
	CHECK_ESPCALL(gpio_config(&tmp_gpio_conf), NIBBLE_GPIO_CONFIG_FAILURE, "gpio_config() failed");
	CHECK_ESPCALL(gpio_install_isr_service(0), NIBBLE_GPIO_INSTALL_ISR_FAILURE, "gpio_install_isr_service() failed");
	return _stat;
}

status_t gpioman_setdown(void)
{
	status_t _stat = NIBBLE_SUCCESS;
	gpio_uninstall_isr_service();
	return _stat;
}

status_t gpioman_config_pin(gpioman_pin_t *pin)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(gpio_set_direction(pin->gpio_num, pin->mode), NIBBLE_GPIO_MODE_FAILURE, "gpio_set_direction() failed");
	switch (pin->mode) {
	case GPIO_MODE_INPUT :
		CHECK_ESPCALL(gpio_pullup_en(pin->gpio_num), NIBBLE_GPIO_PULLUP_EN_FAILURE, "gpio_pullup_en() failed");
		CHECK_ESPCALL(gpio_set_intr_type(pin->gpio_num, pin->intr_type), NIBBLE_GPIO_INTR_TYPE_FAILURE, "gpio_set_intr_type() failed");
		CHECK_ESPCALL(gpio_isr_handler_add(pin->gpio_num, pin->handler, (void *) &pin->gpio_num), NIBBLE_GPIO_ADD_ISR_HANDLER_FAILURE, "gpio_isr_handler_add() failed");
		break;
	case GPIO_MODE_OUTPUT :
		CHECK_ESPCALL(gpio_set_level(pin->gpio_num, pin->level), NIBBLE_GPIO_SET_LEVEL_FAILURE, "gpio_set_level() failed");
		break;
	default :
		ESP_LOGW(LOGTAG, "GPIO_MODE_OUTPUT_OD ignored");
	}
	return _stat;
}

status_t gpioman_modify_level(gpioman_pin_t *pin, uint32_t level)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_EQUAL(pin->mode, GPIO_MODE_OUTPUT, NIBBLE_GPIO_NOT_OUTPUT_FAILURE, "gpio mode OUTPUT required for setting level");
	CHECK_ESPCALL(gpio_set_level(pin->gpio_num, level), NIBBLE_GPIO_SET_LEVEL_FAILURE, "gpio_set_level() failed");
	pin->level = level;
	return _stat;
}

status_t gpioman_modify_handler(gpioman_pin_t *pin, gpio_isr_t handler)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_EQUAL(pin->mode, GPIO_MODE_INPUT, NIBBLE_GPIO_NOT_INPUT_FAILURE, "gpio mode INPUT required for setting handler");
	CHECK_ESPCALL(gpio_isr_handler_remove(pin->gpio_num), NIBBLE_GPIO_REMOVE_ISR_HANDLER_FAILURE, "gpio_isr_handler_remove() failed");
	CHECK_ESPCALL(gpio_isr_handler_add(pin->gpio_num, pin->handler, NULL), NIBBLE_GPIO_ADD_ISR_HANDLER_FAILURE, "gpio_isr_handler_add() failed");
	pin->handler = handler;
	return _stat;
}
