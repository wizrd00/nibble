#ifndef NIBBLE_SSD1306_H
#define NIBBLE_SSD1306_H

// OLED Monitor Module SSD-1306 128x64 pixels

/*
** monman config format
** +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
** |   mux ratio (15-63)   |   seg remap (0 or 1)  |   com remap (0 or 1)  |
** +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
** size = 3 * sizeof(uint8_t);
*/

#include "types.h"
#include "i2cman.h"

#define SCREEN_LENGTH_SIZE 0x80
#define SCREEN_WIDTH_SIZE 0x40
#define SCREEN_PAGE_LENGHT_SIZE 0x80
#define SCREEN_PAGE_WIDTH_SIZE 0x08

#define SCREEN_ADDRESS 0x3d

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

#define CONFIG_COMMAND_SIZE 0x0d

#define CHECK_BUS_STAT(val, ...)\
	do {if (val != NIBBLE_SUCCESS) {ESP_LOGE(LOGTAG, __VA_ARGS__); return _stat = MONITOR_BUS_FAILURE;}} while (0)

monitor_status_t monitor_driver_setup(void);

monitor_status_t monitor_driver_config(uint8_t *conf);

monitor_status_t monitor_driver_display_on(void);

monitor_status_t monitor_driver_display_off(void);

monitor_status_t monitor_driver_sleep(void);

monitor_status_t monitor_driver_set_contrast(uint8_t value);

monitor_status_t monitor_driver_display(uint8_t **matrix, int start_seg, int end_seg, int start_com, int end_com);

monitor_status_t monitor_driver_set_pixel(uint8_t pixel, int pixel_x, int pixel_y);

static inline void scrcmd_encode_page(uint8_t **page, uint8_t page_len, uint8_t *buf, size_t *buf_len)
{
	
	for (int i = 0; i < SCREEN_PAGE_WIDTH_SIZE; i++)
		for (int j = 0; j < page_len; j++)
			buf[j] |= page[i][j] << (SCREEN_PAGE_WIDTH_SIZE - i - 1);
	*buf_len = page_len;
	return;
}

#endif
