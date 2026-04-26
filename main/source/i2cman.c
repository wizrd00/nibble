#include "i2cman.h"

status_t i2cman_setup(i2cman_conf_t *conf)
{
	status_t _stat = NIBBLE_SUCCESS;
	i2c_config_t tmp_i2c_conf = {
		.mode = I2CMAN_MODE,
		.sda_io_num = conf->sda_gpio_num,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_io_num = conf->scl_gpio_num,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.clk_stretch_tick = conf->clock_tick
	};
	CHECK_ESPCALL(i2c_driver_install(I2CMAN_PORT, I2CMAN_MODE), NIBBLE_I2C_DRIVER_INSTALL_FAILURE, "i2c_driver_install() failed");
	CHECK_ESPCALL(i2c_param_config(I2CMAN_PORT, &tmp_i2c_conf), NIBBLE_I2C_CONFIG_FAILURE, "i2c_param_config() failed");
	return _stat;
}

status_t i2cman_setdown(void)
{
	status_t _stat = NIBBLE_SUCCESS;
	CHECK_ESPCALL(i2c_driver_delete(I2CMAN_PORT), NIBBLE_I2C_DRIVER_DELETE_FAILURE, "i2c_driver_delete() failed");
	return _stat;
}

status_t i2cman_send(int8_t addr, void *data, size_t data_len, bool ack_check, TickType_t timeout)
{
	status_t _stat = NIBBLE_SUCCESS;
	esp_err_t esp_stat = ESP_OK;
	CHECK_GREATER(addr, 0x00, NIBBLE_I2C_INVALID_ADDR, "the address must be 7-bit");
	uint8_t addr_rw_data = ((uint8_t) addr << 1) | I2CMAN_SEND;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	CHECK_ESPCALL(i2c_master_start(cmd), NIBBLE_I2C_START_FAILURE, "i2c_master_start() failed");
	CHECK_ESPCALL(i2c_master_write_byte(cmd, addr_rw_data, ack_check), NIBBLE_I2C_WRITE_ADDR_RW_FAILURE, "i2c_master_write_byte() failed");
	CHECK_ESPCALL(i2c_master_write(cmd, (uint8_t *) data, data_len, ack_check), NIBBLE_I2C_WRITE_DATA_FAILURE, "i2c_master_write() failed");
	CHECK_ESPCALL(i2c_master_stop(cmd), NIBBLE_I2C_STOP_FAILURE, "i2c_master_stop() failed");
	switch ((esp_stat = i2c_master_cmd_begin(I2CMAN_PORT, cmd, timeout))) {
	case ESP_OK :
		break;
	case ESP_FAIL :
		CHECK_ESPCALL(esp_stat, NIBBLE_I2C_SLAVE_NOT_ACK_FAILURE, "the slave doesn't ACK");
		break;
	case ESP_ERR_TIMEOUT :
		CHECK_ESPCALL(esp_stat, NIBBLE_I2C_SEND_TIMEOUT_FAILURE, "operation timeout because the bus is busy");
		break;
	default :
		CHECK_ESPCALL(esp_stat, NIBBLE_I2C_SEND_FAILURE, "i2c_master_cmd_begin() failed");
	}
	i2c_cmd_link_delete(cmd);
	return _stat;
}

status_t i2cman_recv(int8_t addr, void *data, size_t data_len, TickType_t timeout)
{
	status_t _stat = NIBBLE_SUCCESS;
	esp_err_t esp_stat = ESP_OK;
	CHECK_GREATER(addr, 0x00, NIBBLE_I2C_INVALID_ADDR, "the address must be 7-bit");
	uint8_t addr_rw_data = ((uint8_t) addr << 1) | I2CMAN_RECV;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	CHECK_ESPCALL(i2c_master_start(cmd), NIBBLE_I2C_START_FAILURE, "i2c_master_start() failed");
	CHECK_ESPCALL(i2c_master_write_byte(cmd, addr_rw_data, true), NIBBLE_I2C_WRITE_ADDR_RW_FAILURE, "i2c_master_write_byte() failed");
	CHECK_ESPCALL(i2c_master_read(cmd, (uint8_t *) data, data_len, I2CMAN_ACKV), NIBBLE_I2C_READ_DATA_FAILURE, "i2c_master_read() failed");
	CHECK_ESPCALL(i2c_master_stop(cmd), NIBBLE_I2C_STOP_FAILURE, "i2c_master_stop() failed");
	switch ((esp_stat = i2c_master_cmd_begin(I2CMAN_PORT, cmd, timeout))) {
	case ESP_OK :
		break;
	case ESP_FAIL :
		CHECK_ESPCALL(esp_stat, NIBBLE_I2C_SLAVE_NOT_ACK_FAILURE, "the slave doesn't ACK");
		break;
	case ESP_ERR_TIMEOUT :
		CHECK_ESPCALL(esp_stat, NIBBLE_I2C_RECV_TIMEOUT_FAILURE, "operation timeout because the bus is busy");
		break;
	default :
		CHECK_ESPCALL(esp_stat, NIBBLE_I2C_RECV_FAILURE, "i2c_master_cmd_begin() failed");
	}
	i2c_cmd_link_delete(cmd);
	return _stat;
}
