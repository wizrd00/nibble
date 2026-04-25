#include "adcman.h"

status_t adcman_setup(adcman_conf_t *conf)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(adc_init(&conf->adc_conf), NIBBLE_ADC_INIT_FAILURE, "adc_init() failed");
	return _stat;
}

status_t adcman_setdown(void)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(adc_deinit(), NIBBLE_ADC_DEINIT_FAILURE, "adc_deinit() failed");
	return _stat;
}

status_t adcman_calibrate(adcman_conf_t *conf)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(adc_read(&conf->origin), NIBBLE_ADC_CALIBRATE_FAILURE, "adc_read() failed");
	return _stat;
}

status_t adcman_measure(adcman_conf_t *conf, uint16_t *value)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(adc_read(value), NIBBLE_ADC_MEASURE_FAILURE, "adc_read() failed");
	return _stat;
}
