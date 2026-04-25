#include "nibble.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static xQueueHandle gpio_evt_queue = NULL;

static void buttom_handler(void *arg)
{
	gpio_num_t *gpio_num = (gpio_num_t *) arg;
	xQueueSendFromISR(gpio_evt_queue, gpio_num, NULL);
	return;
}

static void buttom_task(void *arg)
{
	uint32_t io_num;
	while (1) {
		if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
			ESP_LOGI(LOGTAG, "CLICK\nGPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
		}
	}
}

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
		.origin = 0,
		.adc_conf = {
			.mode = ADC_READ_TOUT_MODE,
			.clk_div = 8
		}
	};
	uint16_t adc_value = 0;
	gpioman_conf_t gpio_conf = {.pin_mask = GPIO_Pin_5};
	gpioman_pin_t buttom = {
		.level = 0,
		.gpio_num = GPIO_NUM_5,
		.mode = GPIO_MODE_INPUT,
		.intr_type = GPIO_INTR_NEGEDGE,
		.handler = buttom_handler
	};
	gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
	xTaskCreate(buttom_task, "gpio_task_example", 2048, NULL, 10, NULL);
	TRY(adcman_setup(&adc_conf), "adcman_setup() failed");
	TRY(adcman_calibrate(&adc_conf), "adcman_calibrate() failed");
	ESP_LOGI(LOGTAG, "origin = %d", adc_conf.origin);
	TRY(gpioman_setup(&gpio_conf), "gpioman_setup() failed");
	TRY(gpioman_config_pin(&buttom), "gpioman_config_pin() failed");
	while (1) {
		if (adcman_measure(&adc_conf, &adc_value) != NIBBLE_SUCCESS)
			ESP_LOGE(LOGTAG, "measure failure");
		if (adc_value != adc_conf.origin) {
			ESP_LOGW(LOGTAG, "joystick moved %d", adc_value);
		}
		usleep(100000);
	}
	return;
}
