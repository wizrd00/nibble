#include "adcman.h"

status_t adcman_setup(adcman_conf_t *conf)
{
	status_t _stat = NIBBLE_SUCCESS;
	adc_config_t tmp_adc_conf = {
		.mode = conf->mode,
		.clk_div = 8
	};
	CHECK_ESPCALL(adc_init(&tmp_adc_conf), NIBBLE_ADC_INIT_FAILURE, "adc_init() failed");
	return _stat;
}

status_t adcman_setdown(void)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(adc_deinit(), NIBBLE_ADC_DEINIT_FAILURE, "adc_deinit() failed");
	return _stat;
}

status_t adcman_measure(uint16_t *value)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(adc_read(value), NIBBLE_ADC_MEASURE_FAILURE, "adc_read() failed");
	return _stat;
}
