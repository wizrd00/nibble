#include "driver/ssd1306.h"

static i2cman_conf_t *bus_conf;

monitor_status_t monitor_driver_setup(i2cman_conf_t *i2cman_conf)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	bus_conf = i2cman_conf;
	CHECK_BUS_STAT(i2cman_setup(bus_conf), "i2cman_setup() failed");
	return _stat;
}

monitor_status_t monitor_driver_config(uint8_t *conf)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	uint8_t cmd[CONFIG_COMMAND_SIZE];
	uint8_t ratio = conf[0], seg_remap = conf[1], com_remap = conf[2];
	if ((ratio < SCREEN_COMMAND_MIN_MULTIPLEX_RATIO) || (ratio > SCREEN_COMMAND_MAX_MULTIPLEX_RATIO))
		return _stat = MONITOR_INVALID_MULTIPLEX_RATIO;
	if (seg_remap > 1)
		return _stat = MONITOR_INVALID_SEG_REMAP_BOOL;
	if (com_remap > 1)
		return _stat = MONITOR_INVALID_COM_REMAP_BOOL;
	cmd[0] = (uint8_t) SCREEN_COMMAND_MULTIPLEX_RATIO;
	cmd[1] = ratio;
	cmd[2] = (uint8_t) SCREEN_COMMAND_ADDRESSING_MODE;
	cmd[3] = (uint8_t) SCREEN_COMMAND_HORIZONTAL_ADDRESSING_MODE;
	cmd[4] = (uint8_t) (seg_remap == 1) ? SCREEN_COMMAND_SEG_REMAP_ON : SCREEN_COMMAND_SEG_REMAP_OFF;
	cmd[5] = (uint8_t) SCREEN_COMMAND_COM_HARDWARE_CONFIG;
	cmd[6] = (uint8_t) (com_remap == 1) ? SCREEN_COMMAND_COM_REMAP_ON : SCREEN_COMMAND_COM_REMAP_OFF;
	cmd[7] = (uint8_t) SCREEN_COMMAND_CONTRAST_SETTING;
	cmd[8] = (uint8_t) SCREEN_COMMAND_MIN_CONTRAST;
	cmd[9] = (uint8_t) SCREEN_COMMAND_ENTIRE_DISPLAY_ON_WITHOUT_RAM;
	cmd[10] = (uint8_t) SCREEN_COMMAND_DISPLAY_NORMAL;
	cmd[11] = (uint8_t) SCREEN_COMMAND_PUMP_CHARGE_SETTING;
	cmd[12] = (uint8_t) SCREEN_COMMAND_PUMP_CHARGE_ON;
	return _stat;
}
