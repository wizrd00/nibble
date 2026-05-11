#ifndef RAVEN_TYPES_H
#define RAVEN_TYPES_H

#include "esp_log.h"
#include "esp_err.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define LOGTAG "NIBBLE"
#define LOGERR "[ERROR][ESP_ERR=%s]"

#define CHECK_STAT(val, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); return _stat = val;}} while (0)

#define CHECK_STAT_FREE(val, ptr, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); free((void *) ptr); ptr = NULL; return _stat = val;}} while (0)

#define CHECK_STAT_CLOSE(val, ofd, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); close((int) ofd); return _stat = val;}} while (0)

#define CHECK_EQUAL(val0, val1, err, ...)\
	do {if (val0 != val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); return _stat = err;}} while (0)

#define CHECK_EQUAL_FREE(val0, val1, ptr, err, ...)\
	do {if (val0 != val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); free((void *) ptr); ptr = NULL; return _stat = err;}} while (0)

#define CHECK_EQUAL_CLOSE(val0, val1, ofd, err, ...)\
	do {if (val0 != val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); close((int) ofd); return _stat = err;}} while (0)

#define CHECK_NOTEQUAL(val0, val1, err, ...)\
	do {if (val0 == val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); return _stat = err;}} while (0)

#define CHECK_NOTEQUAL_FREE(val0, val1, ptr, err, ...)\
	do {if (val0 == val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); free((void *) ptr); ptr = NULL; return _stat = err;}} while (0)

#define CHECK_NOTEQUAL_CLOSE(val0, val1, ofd, err, ...)\
	do {if (val0 == val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); close((int) ofd); return _stat = err;}} while (0)

#define CHECK_GREATER(val0, val1, err, ...)\
	do {if ((double) val0 <= (double) val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); return _stat = err;}} while (0)

#define CHECK_GREATER_FREE(val0, val1, ptr, err, ...)\
	do {if ((double) val0 <= (double) val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); free((void *) ptr); ptr = NULL; return _stat = err;}} while (0)

#define CHECK_GREATER_CLOSE(val0, val1, ofd, err, ...)\
	do {if ((double) val0 <= (double) val1) {ESP_LOGE(LOGTAG, __VA_ARGS__); close( (int) ofd); return _stat = err;}} while (0)

#define CHECK_ESPCALL(val, err, ...)\
	do {if (val != ESP_OK) {ESP_LOGE(LOGTAG, __VA_ARGS__); ESP_LOGE(LOGTAG, LOGERR, esp_err_to_name(val)); return _stat = err;}} while (0)

#define CHECK_ESPCALL_FREE(val, ptr, err, ...)\
	do {if (val != ESP_OK) {ESP_LOGE(LOGTAG, __VA_ARGS__); ESP_LOGE(LOGTAG, LOGERR, esp_err_to_name(val)); free((void *) ptr); ptr = NULL; return _stat = err;}} while (0)

#define CHECK_ESPCALL_CLOSE(val, ofd, err, ...)\
	do {if (val != ESP_OK) {ESP_LOGE(LOGTAG, __VA_ARGS__); ESP_LOGE(LOGTAG, LOGERR, esp_err_to_name(val)); close((int) ofd); return _stat = err;}} while (0)

#define TRY(val, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); setdown(); return;}} while (0)

typedef enum {
	NIBBLE_SUCCESS,
	NIBBLE_ADC_INIT_FAILURE,
	NIBBLE_ADC_DEINIT_FAILURE,
	NIBBLE_ADC_CALIBRATE_FAILURE,
	NIBBLE_ADC_MEASURE_FAILURE,
	NIBBLE_GPIO_CONFIG_FAILURE,
	NIBBLE_GPIO_INSTALL_ISR_FAILURE,
	NIBBLE_GPIO_MODE_FAILURE,
	NIBBLE_GPIO_PULLUP_EN_FAILURE,
	NIBBLE_GPIO_INTR_TYPE_FAILURE,
	NIBBLE_GPIO_ADD_ISR_HANDLER_FAILURE,
	NIBBLE_GPIO_SET_LEVEL_FAILURE,
	NIBBLE_GPIO_NOT_OUTPUT_FAILURE,
	NIBBLE_GPIO_NOT_INPUT_FAILURE,
	NIBBLE_GPIO_REMOVE_ISR_HANDLER_FAILURE,
	NIBBLE_I2C_DRIVER_INSTALL_FAILURE,
	NIBBLE_I2C_CONFIG_FAILURE,
	NIBBLE_I2C_DRIVER_DELETE_FAILURE,
	NIBBLE_I2C_INVALID_ADDR,
	NIBBLE_I2C_START_FAILURE,
	NIBBLE_I2C_WRITE_ADDR_RW_FAILURE,
	NIBBLE_I2C_WRITE_DATA_FAILURE,
	NIBBLE_I2C_STOP_FAILURE,
	NIBBLE_I2C_SLAVE_NOT_ACK_FAILURE,
	NIBBLE_I2C_SEND_TIMEOUT_FAILURE,
	NIBBLE_I2C_SEND_FAILURE,
	NIBBLE_I2C_READ_DATA_FAILURE,
	NIBBLE_I2C_RECV_TIMEOUT_FAILURE,
	NIBBLE_I2C_RECV_FAILURE
} status_t;

typedef enum {
	MONITOR_SUCCESS,
	MONITOR_FAILURE
} monitor_status_t;

typedef struct {
	uint8_t **floor_mx;
	uint8_t **float_mx;
	size_t len;
	size_t wid;
} matrix_t;

#endif
