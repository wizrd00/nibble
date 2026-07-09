#include "driver/ssd1306.h"

static i2cman_conf_t *bus_conf;
static TickType_t bus_timeout;

static void encode_page(uint8_t **page, uint8_t page_len, uint8_t *buf)
{
	
	for (int i = 0; i < SCREEN_PAGE_WIDTH_SIZE; i++)
		for (int j = 0; j < page_len; j++)
			buf[j] |= page[i][j] << (SCREEN_PAGE_WIDTH_SIZE - i - 1);
	return;
}

monitor_status_t monitor_driver_setup(i2cman_conf_t *i2cman_conf)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	bus_conf = i2cman_conf;
	CHECK_BUS_STAT(i2cman_setup(bus_conf), "i2cman_setup() failed");
	return _stat;
}

monitor_status_t monitor_driver_setdown(void)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	CHECK_BUS_STAT(i2cman_setdown(), "i2cman_setdown() failed");
	return _stat;
}

monitor_status_t monitor_driver_config(uint8_t *conf)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	uint8_t cmd[CONFIG_COMMAND_SIZE];
	uint8_t ratio = conf[0], seg_remap = conf[1], com_remap = conf[2];
	bus_timeout = (TickType_t) conf[3];
	if ((ratio < SCREEN_COMMAND_MIN_MULTIPLEX_RATIO) || (ratio > SCREEN_COMMAND_MAX_MULTIPLEX_RATIO))
		return _stat = MONITOR_INVALID_MULTIPLEX_RATIO;
	if (seg_remap > 1)
		return _stat = MONITOR_INVALID_SEG_REMAP_BOOL;
	if (com_remap > 1)
		return _stat = MONITOR_INVALID_COM_REMAP_BOOL;
	cmd[0] = (uint8_t) SCREEN_CONTROL_COMMAND;
	cmd[1] = (uint8_t) SCREEN_COMMAND_MULTIPLEX_RATIO;
	cmd[2] = ratio;
	cmd[3] = (uint8_t) SCREEN_COMMAND_ADDRESSING_MODE;
	cmd[4] = (uint8_t) SCREEN_COMMAND_HORIZONTAL_ADDRESSING_MODE;
	cmd[5] = (uint8_t) (seg_remap == 1) ? SCREEN_COMMAND_SEG_REMAP_ON : SCREEN_COMMAND_SEG_REMAP_OFF;
	cmd[6] = (uint8_t) SCREEN_COMMAND_COM_HARDWARE_CONFIG;
	cmd[7] = (uint8_t) (com_remap == 1) ? SCREEN_COMMAND_COM_REMAP_ON : SCREEN_COMMAND_COM_REMAP_OFF;
	cmd[8] = (uint8_t) SCREEN_COMMAND_CONTRAST_SETTING;
	cmd[9] = (uint8_t) SCREEN_COMMAND_MIN_CONTRAST;
	cmd[10] = (uint8_t) SCREEN_COMMAND_ENTIRE_DISPLAY_ON_WITHOUT_RAM;
	cmd[11] = (uint8_t) SCREEN_COMMAND_DISPLAY_NORMAL;
	cmd[12] = (uint8_t) SCREEN_COMMAND_PUMP_CHARGE_SETTING;
	cmd[13] = (uint8_t) SCREEN_COMMAND_PUMP_CHARGE_ON;
	CHECK_BUS_STAT(i2cman_send((int8_t) SCREEN_ADDRESS, (void *) cmd, (size_t) CONFIG_COMMAND_SIZE, true, bus_timeout), "i2cman_send() failed");
	return _stat;
}

monitor_status_t monitor_driver_display_on(void)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	uint8_t cmd[DISPLAY_ON_COMMAND_SIZE];
	cmd[0] = (uint8_t) SCREEN_CONTROL_COMMAND;
	cmd[1] = (uint8_t) SCREEN_COMMAND_DISPLAY_ON;
	CHECK_BUS_STAT(i2cman_send((int8_t) SCREEN_ADDRESS, (void *) cmd, (size_t) DISPLAY_ON_COMMAND_SIZE, true, bus_timeout), "i2cman_send() failed");
	return _stat;
}

monitor_status_t monitor_driver_display_off(void)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	uint8_t cmd[DISPLAY_OFF_COMMAND_SIZE];
	cmd[0] = (uint8_t) SCREEN_CONTROL_COMMAND;
	cmd[1] = (uint8_t) SCREEN_COMMAND_DISPLAY_OFF;
	CHECK_BUS_STAT(i2cman_send((int8_t) SCREEN_ADDRESS, (void *) cmd, (size_t) DISPLAY_OFF_COMMAND_SIZE, true, bus_timeout), "i2cman_send() failed");
	return _stat;
}

monitor_status_t monitor_driver_sleep(void)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	return _stat = monitor_driver_display_off();
}

monitor_status_t monitor_driver_set_contrast(uint8_t value)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	uint8_t cmd[SET_CONTRAST_COMMAND_SIZE];
	if (value == 0)
		return _stat = MONITOR_INVALID_CONTRAST_VALUE;
	cmd[0] = (uint8_t) SCREEN_CONTROL_COMMAND;
	cmd[1] = (uint8_t) SCREEN_COMMAND_CONTRAST_SETTING;
	cmd[2] = (uint8_t) value;
	CHECK_BUS_STAT(i2cman_send((int8_t) SCREEN_ADDRESS, (void *) cmd, (size_t) SET_CONTRAST_COMMAND_SIZE, true, bus_timeout), "i2cman_send() failed");
	return _stat;
}

monitor_status_t monitor_driver_display(uint8_t **matrix, int start_col, int end_col, int start_page, int end_page)
{
	monitor_status_t _stat = MONITOR_SUCCESS;
	uint8_t cmd[DISPLAY_COMMAND_SIZE];
	if (start_col > end_col)
		return _stat = MONITOR_INVALID_START_END_COLUMN_COMBINATION;
	if ((start_col < SCREEN_START_COLUMN) || (start_col > SCREEN_END_COLUMN))
		return _stat = MONITOR_INVALID_START_COLUMN;
	if ((end_col < SCREEN_START_COLUMN) || (end_col > SCREEN_END_COLUMN))
		return _stat = MONITOR_INVALID_END_COLUMN;
	if (start_page > end_page)
		return _stat = MONITOR_INVALID_START_END_PAGE_COMBINATION;
	if ((start_page < SCREEN_START_PAGE) || (start_page > SCREEN_END_PAGE))
		return _stat = MONITOR_INVALID_START_PAGE;
	if ((end_page < SCREEN_START_PAGE) || (end_page > SCREEN_END_PAGE))
		return _stat = MONITOR_INVALID_END_PAGE;
	cmd[0] = (uint8_t) SCREEN_CONTROL_COMMAND;
	cmd[1] = (uint8_t) SCREEN_COMMAND_SET_COLUMN;
	cmd[2] = (uint8_t) start_col;
	cmd[3] = (uint8_t) end_col;
	cmd[4] = (uint8_t) SCREEN_COMMAND_SET_PAGE;
	cmd[5] = (uint8_t) start_page;
	cmd[6] = (uint8_t) end_page;
	CHECK_BUS_STAT(i2cman_send((int8_t) SCREEN_ADDRESS, (void *) cmd, (size_t) DISPLAY_COMMAND_SIZE, true, bus_timeout), "i2cman_send() failed");
	size_t buf_len = (size_t) (PAGE_LENGTH(start_col, end_col) + 1);
	uint8_t *buf = (uint8_t *) malloc(buf_len);
	if (buf == NULL)
		return _stat = MONITOR_MEMORY_FAILURE;
	for (int i = 0; i < PAGE_COUNT(start_page, end_page); i++) {
		memset(buf, 0, buf_len);
		encode_page(matrix + i * SCREEN_PAGE_WIDTH_SIZE, PAGE_LENGTH(start_col, end_col), buf + 1);
		CHECK_BUS_STAT_FREE(i2cman_send((int8_t) SCREEN_ADDRESS, (void *) buf, buf_len, true, bus_timeout), buf, "i2cman_send() failed");
	}
	free((void *) buf);
	return _stat;
}
