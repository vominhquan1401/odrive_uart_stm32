#include "uart.h"

void default_command(command_val *val){
	 for (int i = 0; i < 11 ; ++i) {
		sprintf((char *)val->str, "%s", val->commands[i]);
		HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
	 }
		sprintf((char *)val->str, "%s", val->commands[22]);
		HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
	  sprintf((char *)val->str, "%s", val->commands[11]);
		HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
	  val->time_uart = HAL_GetTick();
	 while (HAL_GetTick() - val->time_uart < 2000) {
		 
    }
	 for (int i = 12; i < 21 ; ++i) {
		sprintf((char *)val->str, "%s", val->commands[i]);
		HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
	 }
	 sprintf((char *)val->str, "%s", val->commands[22]);
	 HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
}
void handle_command(command_val *val){
	if (val->uart_flag)
		{
			switch (val->data_rx[0]) {
        case 'e':
					if (strstr((char *)val->data_rx, "enable") != 0) {
							sprintf((char *)val->str, "%s", val->commands[20]);
						HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
					}
					break;
        case 'd':
					if (strstr((char *)val->data_rx, "disable") != 0) {
							sprintf((char *)val->str, "%s", val->commands[10]);
						HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
					}
					break;
        case 'v':
					if (strstr((char *)val->data_rx, "vel") != 0) {
							sscanf((char *)val->data_rx, "vel %hhu", &val->vel_value);
							sprintf((char *)val->str, val->commands[24], val->vel_value);
						HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
					}
					break;
        case 'p':
					if (strstr((char *)val->data_rx, "pos") != 0) {
							sscanf((char *)val->data_rx, "pos %hhu", &val->pos_value);
							sprintf((char *)val->str, val->commands[23], val->pos_value);
						HAL_UART_Transmit(val->uart,val->str,strlen((char *)val->str),100);
					}
					break;
				}
			val->uart_flag = 0;
			memset(val->data_rx,'\0', 7);
		}
}
void uart_init(command_val *val,UART_HandleTypeDef *uart){
	val->uart_flag=0;
	val->count=0;
	val->vel_value=0;
	val->pos_value=0;
	val->time_uart=0;
	val->uart = uart;
	val->commands[0] = "w config.enable_brake_resistor True\n";
	val->commands[1] = "w config.brake_resistance 2\n";
	val->commands[2] = "w config.dc_max_negative_current -3\n";
	val->commands[3] = "w axis1.encoder.config.cpr 4000\n";
	val->commands[4] = "w axis1.motor.config.calibration_current 8\n";
	val->commands[5] = "w axis1.motor.config.current_lim 10\n";
	val->commands[6] = "w axis1.motor.config.pole_pairs 7\n";
	val->commands[7] = "w axis1.motor.config.torque_constant 8.27/140\n";
	val->commands[8] = "w axis1.motor.config.motor_type MOTOR_TYPE_HIGH_CURRENT\n";
	val->commands[9] = "w axis1.controller.config.vel_limit 20\n";
	val->commands[10] = "w axis1.requested_state AXIS_STATE_IDLE\n";
	val->commands[11] = "w axis1.requested_state AXIS_STATE_FULL_CALIBRATION_SEQUENCE\n";
	val->commands[12] = "w axis1.encoder.config.pre_calibrated True\n";
	val->commands[13] = "w axis1.config.startup_encoder_index_search True\n";
	val->commands[14] = "w axis1.config.startup_motor_calibration True\n";
	val->commands[15] = "w axis1.config.startup_closed_loop_control True\n";
	val->commands[16] = "w axis1.controller.input_pos 1\n";
	val->commands[17] = "w axis1.controller.config.control_mode 2\n";
	val->commands[18] = "w axis1.controller.config.input_mode 2\n";
	val->commands[19] = "w axis1.controller.config.vel_ramp_rate 5\n";
	val->commands[20] = "w axis1.requested_state AXIS_STATE_CLOSED_LOOP_CONTROL\n";
	val->commands[21] = "w axis1.controller.input_vel 5\n";
	val->commands[22] = "ss\n";
	val->commands[23] = "t 1 %d\n";
	val->commands[24] = "v 1 %d 0\n";
}
