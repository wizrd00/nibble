#include "nibble.h"

void setdown(void)
{
	adcman_setdown();
	gpioman_setdown();
	exit(EXIT_FAILURE);
	return;
}

void app_main(void)
{
	adcman_conf_t adc_conf = {
		.mode = ADC_READ_TOUT_MODE,
	};
	gpioman_conf_t gpio_conf = {.pin_mask = GPIO_Pin_5 | GPIO_Pin_16};
	gpioman_pin_t button = {
		.level = 0,
		.gpio_num = GPIO_NUM_0,
		.mode = GPIO_MODE_INPUT,
		.intr_type = GPIO_INTR_ANYEDGE,
		.handler = NULL
	};
	gpioman_pin_t led = {
		.level = 0,
		.gpio_num = GPIO_NUM_16,
		.mode = GPIO_MODE_OUTPUT
	};
	int joystick_pos;
	int button_pos;
	TRY(adcman_setup(&adc_conf), "adcman_setup() failed");
	TRY(gpioman_setup(&gpio_conf), "gpioman_setup() failed");
	TRY(gpioman_config_pin(&button), "gpioman_config_pin() failed");
	TRY(gpioman_config_pin(&led), "gpioman_config_pin() failed");
	while (1) {
		if (joyman_joystick_position(&joystick_pos) != NIBBLE_SUCCESS) {
			ESP_LOGE(LOGTAG, "joyman_joystick_position() failed");
		} else {
			ESP_LOGW(LOGTAG, "joystick position %d\n", joystick_pos);
		}
		if (joyman_button_status(button.gpio_num, &button_pos) != NIBBLE_SUCCESS) {
			ESP_LOGE(LOGTAG, "joyman_button_status() failed");
		} else {
			ESP_LOGW(LOGTAG, "button status level is %d\n", button_pos);
			if (button_pos == 1)
				gpioman_modify_level(&led, 0x01);
			else
				gpioman_modify_level(&led, 0x00);
		}
		printf("\n");
		usleep(100000);
	}
	return;
}
