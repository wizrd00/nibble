#ifndef NIBBLE_SSD1306_H
#define NIBBLE_SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_MAX_COMMAND_SIZE 0x06
#define SCREEN_MAX_RATIO_SIZE 0x40
#define SCREEN_PIXELS_SIZE 0x2000
#define SCREEN_BUFFER_SIZE 0x400
#define SCREEN_LENGTH_SIZE 0x80
#define SCREEN_WIDTH_SIZE 0x40

#define SCREEN_ADDRESS 0x3d

#define SCREEN_CONTROL_DATA 0x00
#define SCREEN_CONTROL_COMMAND 0x80

#define SCREEN_COMMAND_ADDRESSING_MODE 0x20
#define SCREEN_COMMAND_SEG_REMAP_OFF 0xa0
#define SCREEN_COMMAND_SEG_REMAP_ON 0xa1
#define SCREEN_COMMAND_COM_REMAP_OFF 0xc0
#define SCREEN_COMMAND_COM_REMAP_ON 0xc8
#define SCREEN_COMMAND_MULTIPLEX_RATIO 0xa8

#define SCREEN_COMMAND_ADDRESSING_MODE 0x20

#define SCREEN_COMMAND_CONTRAST 0x81

#define SCREEN_COMMAND_ENTIRE_DISPLAY_ON_WITH_RAM 0xa4
#define SCREEN_COMMAND_ENTIRE_DISPLAY_ON_WITHOUT_RAM 0xa5
#define SCREEN_COMMAND_DISPLAY_NORMAL 0xa6
#define SCREEN_COMMAND_DISPLAY_INVERSE 0xa7
#define SCREEN_COMMAND_DISPLAY_OFF 0xae
#define SCREEN_COMMAND_DISPLAY_ON 0xaf

static inline void scrcmd_control_data(uint8_t *cmd, size_t *len)
{
	cmd[0] = (uint8_t) SCREEN_CONTROL_DATA;
	*len = 1;
	return;
}

static inline void scrcmd_control_command(uint8_t *cmd, size_t *len)
{
	cmd[0] = (uint8_t) SCREEN_CONTROL_COMMAND;
	*len = 1;
	return;
}

static inline void scrcmd_device_setup(uint8_t *cmd, size_t *len, uint8_t ratio, bool x_remap, bool y_remap)
{
	cmd[0] = (uint8_t) SCREEN_COMMAND_ADDRESSING_MODE;
	cmd[1] = (uint8_t) 0x00;
	cmd[2] = (uint8_t) SCREEN_COMMAND_MULTIPLEX_RATIO;
	cmd[3] = (uint8_t) (ratio <= SCREEN_MAX_RATIO_SIZE) ? ratio - 1 : SCREEN_MAX_RATIO_SIZE - 1;
	cmd[4] = (uint8_t) (x_remap) ? SCREEN_COMMAND_SEG_REMAP_ON : SCREEN_COMMAND_SEG_REMAP_OFF;
	cmd[5] = (uint8_t) (y_remap) ? SCREEN_COMMAND_COM_REMAP_ON : SCREEN_COMMAND_COM_REMAP_OFF;
	*len = 6;
	return;
}

static inline void scrcmd_contrast(uint8_t *cmd, size_t *len, uint8_t val)
{
	cmd[0] = (uint8_t) SCREEN_COMMAND_CONTRAST;
	cmd[1] = val;
	return;
}

static inline void scrcmd_display_off(uint8_t *cmd, size_t *len)
{
	cmd[0] = (uint8_t) SCREEN_COMMAND_DISPLAY_OFF;
	*len = 1;
	return;
}

static inline void scrcmd_display_on(uint8_t *cmd, size_t *len, bool ram_content)
{
	cmd[0] = (uint8_t) (ram_content) ? SCREEN_COMMAND_DISPLAY_ON_WITH_RAM : SCREEN_COMMAND_DISPLAY_ON_WITHOUT_RAM;
	*len = 1;
	return;
}

//TODO

#endif
