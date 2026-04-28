#ifndef NIBBLE_ADCMAN_H
#define NIBBLE_ADCMAN_H

#include "types.h"
#include "driver/adc.h"

#define ADC_MODE_VDD ADC_READ_VDD
#define ADC_MODE_TOUT ADC_READ_TOUT

typedef struct {
	adc_mode_t mode;
} adcman_conf_t;

status_t adcman_setup(adcman_conf_t *conf);

status_t adcman_setdown(void);

status_t adcman_measure(uint16_t *value);

#endif
