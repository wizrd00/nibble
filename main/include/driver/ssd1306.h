#ifndef NIBBLE_SSD1306_H
#define NIBBLE_SSD1306_H

// OLED Monitor Module SSD-1306 128x64 pixels

/*
** monman config format
** +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
** |   mux ratio (15-63)   |   seg remap (0 or 1)  |   com remap (0 or 1)  |   bus timeout (Tick)  |
** +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
** size = 4 * sizeof(uint8_t);
*/

#include "types.h"
#include "i2cman.h"
#include <stdlib.h>
#include <string.h>

#define SCREEN_LENGTH_SIZE 0x80
#define SCREEN_WIDTH_SIZE 0x40
#define SCREEN_PAGE_LENGTH_SIZE 0x80
#define SCREEN_PAGE_WIDTH_SIZE 0x08
#define SCREEN_PAGE_COUNT 0x08
#define SCREEN_START_PAGE 0x00
#define SCREEN_END_PAGE 0x07
#define SCREEN_COLUMN_COUNT 0x80
#define SCREEN_START_COLUMN 0x00
#define SCREEN_END_COLUMN 0x7f

#define SCREEN_ADDRESS 0x3c

#define SCREEN_CONTROL_DATA 0x00
#define SCREEN_CONTROL_COMMAND 0x80

#define SCREEN_COMMAND_NULL 0xe3

#define SCREEN_COMMAND_MULTIPLEX_RATIO 0xa8
#define SCREEN_COMMAND_MIN_MULTIPLEX_RATIO 0x0f
#define SCREEN_COMMAND_MAX_MULTIPLEX_RATIO 0x3f

#define SCREEN_COMMAND_ADDRESSING_MODE 0x20
#define SCREEN_COMMAND_HORIZONTAL_ADDRESSING_MODE 0x00

#define SCREEN_COMMAND_SEG_REMAP_OFF 0xa0
#define SCREEN_COMMAND_SEG_REMAP_ON 0xa1
#define SCREEN_COMMAND_COM_HARDWARE_CONFIG 0xda
#define SCREEN_COMMAND_COM_REMAP_OFF 0x32
#define SCREEN_COMMAND_COM_REMAP_ON 0x12

#define SCREEN_COMMAND_CONTRAST_SETTING 0x81
#define SCREEN_COMMAND_MIN_CONTRAST 0x01
#define SCREEN_COMMAND_MAX_CONTRAST 0xff

#define SCREEN_COMMAND_ENTIRE_DISPLAY_ON_WITH_RAM 0xa4
#define SCREEN_COMMAND_ENTIRE_DISPLAY_ON_WITHOUT_RAM 0xa5
#define SCREEN_COMMAND_DISPLAY_NORMAL 0xa6
#define SCREEN_COMMAND_DISPLAY_INVERSE 0xa7
#define SCREEN_COMMAND_DISPLAY_OFF 0xae
#define SCREEN_COMMAND_DISPLAY_ON 0xaf

#define SCREEN_COMMAND_SET_COLUMN 0x21
#define SCREEN_COMMAND_SET_PAGE 0x22

#define SCREEN_COMMAND_PUMP_CHARGE_SETTING 0x8d
#define SCREEN_COMMAND_PUMP_CHARGE_ON 0x14
#define SCREEN_COMMAND_PUMP_CHARGE_OFF 0x10

#define CONFIG_COMMAND_SIZE 0x0e
#define DISPLAY_ON_COMMAND_SIZE 0x02
#define DISPLAY_OFF_COMMAND_SIZE 0x02
#define SET_CONTRAST_COMMAND_SIZE 0x03
#define DISPLAY_COMMAND_SIZE 0x07

#define PAGE_COUNT(start, end) (end - start + 1)
#define PAGE_LENGTH(start, end) (end - start + 1)

#define CHECK_BUS_STAT(val, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); ESP_LOGE(LOGTAG, "status code of failure = %d", val); return _stat = MONITOR_BUS_FAILURE;}} while (0)

#define CHECK_BUS_STAT_FREE(val, ptr, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); ESP_LOGE(LOGTAG, "status code of failure = %d", val); free((void *) ptr); ptr = NULL; return _stat = MONITOR_BUS_FAILURE;}} while (0)

monitor_status_t monitor_driver_setup(i2cman_conf_t *i2cman_conf);

monitor_status_t monitor_driver_setdown(void);

monitor_status_t monitor_driver_config(uint8_t *conf);

monitor_status_t monitor_driver_display_on(void);

monitor_status_t monitor_driver_display_off(void);

monitor_status_t monitor_driver_sleep(void);

monitor_status_t monitor_driver_set_contrast(uint8_t value);

monitor_status_t monitor_driver_display(uint8_t **matrix, int start_col, int end_col, int start_page, int end_page);

#endif
