#include "nibble.h"

void setdown(void)
{
	adcman_setdown();
	exit(EXIT_FAILURE);
	return;
}

void app_main(void)
{
	adcman_value_t adc_value = ADCMAN_ZERO;
	adcman_conf_t adc_conf = {
		.origin = 0,
		.adc_conf = {
			.mode = ADC_READ_TOUT_MODE,
			.clk_div = 8
		}
	};
	TRY(adcman_setup(&adc_conf), "adcman_setup() failed");
	TRY(adcman_calibrate(&adc_conf), "adcman_calibrate() failed");
	while (1) {
		if (adcman_measure(&adc_conf, &adc_value) != NIBBLE_SUCCESS)
			ESP_LOGE(LOGTAG, "measure failure");
		printf("value %d\n", (int) adc_value);
		usleep(100000);
	}
	return;
}
