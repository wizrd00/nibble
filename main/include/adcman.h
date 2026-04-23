#ifndef NIBBLE_ADCMAN_H
#define NIBBLE_ADCMAN_H

#include "types.h"
#include "driver/adc.h"

#define ADC_MODE_VDD ADC_READ_VDD
#define ADC_MODE_TOUT ADC_READ_TOUT

typedef enum {
	ADCMAN_ZERO,
	ADCMAN_POSITIVE,
	ADCMAN_NEGATIVE
} adcman_value_t;

typedef struct {
	uint16_t origin;
	adc_config_t adc_conf;
} adcman_conf_t;

status_t adcman_setup(adcman_conf_t *conf);

status_t adcman_setdown(void);

status_t adcman_calibrate(adcman_conf_t *conf);

status_t adcman_measure(adcman_conf_t *conf, adcman_value_t *value);

#endif
