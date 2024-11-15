/*
 * fsm_traffic_light.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#include "fsm_traffic_light.h"


void checkTime() {
	if(red_time != yel_time + green_time){
		red_time = yel_time + green_time;
	}
}

void AUTO_LCD() {
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("TRAFFIC1");
	lcd_put_cur(8, 1);
	lcd_send_string("TRAFFIC2");
}

void fsm_traffic(){
	switch(status){
		case INIT:
			checkTime();
			status = RED_GREEN;
			setTimer(0, green_time);
			setTimer(1, 1000);
			break;

		case RED_GREEN:
			val1 = timer_counter[0]/100 + yel_time / 1000;
			val2 = timer_counter[0]/100;
			displayLed(RED);
			displayLed2(GREEN);
			if(isTimerExpired(0)){
				status = RED_YEL;
				setTimer(0, yel_time);
			}
			if (isTimerExpired(1)) {
				AUTO_LCD();
				lcd_put_cur(2, 1);
				sprintf(str, "%d", val1);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				sprintf(str, "%d", val2);
				lcd_send_string(str);
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case RED_YEL:
			val1 = timer_counter[0]/100;
			val2 = timer_counter[0]/100;
			displayLed(RED);
			displayLed2(YEL);
			if(isTimerExpired(0)){
				status = GREEN_RED;
				setTimer(0, green_time);
			}
			if (isTimerExpired(1)) {
				AUTO_LCD();
				lcd_put_cur(2, 1);
				sprintf(str, "%d", val1);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				sprintf(str, "%d", val2);
				lcd_send_string(str);
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case GREEN_RED:
			val1 = timer_counter[0]/100;
			val2 = timer_counter[0]/100 + yel_time / 1000;
			displayLed(GREEN);
			displayLed2(RED);
			if(isTimerExpired(0)){
				status = YEL_RED;
				setTimer(0, yel_time);
			}
			if (isTimerExpired(1)) {
				AUTO_LCD();
				lcd_put_cur(2, 1);
				sprintf(str, "%d", val1);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				sprintf(str, "%d", val2);
				lcd_send_string(str);
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case YEL_RED:
			val1 = timer_counter[0]/100;
			val2 = timer_counter[0]/100;
			displayLed(YEL);
			displayLed2(RED);
			if(isTimerExpired(0)){
				status = RED_GREEN;
				setTimer(0, green_time);
			}
			if (isTimerExpired(1)) {
				AUTO_LCD();
				lcd_put_cur(2, 1);
				sprintf(str, "%d", val1);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				sprintf(str, "%d", val2);
				lcd_send_string(str);
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case MAN_INIT:
			setTimer(0,BLINK_TIME);
			setTimer(1, 1000);
			status = MAN_RED;
			init_Button(1);
			init_Button(2);
			clearLed();
			temp[0] = red_time;
			temp[1] = yel_time;
			temp[2] = green_time;
			break;

		case MAN_RED:
			if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
				setTimer(0, BLINK_TIME);
			}
			if (isTimerExpired(1)) {
				lcd_clear();
				lcd_put_cur(0, 0);
				lcd_send_string("VAL_RED");
				lcd_put_cur(8, 1);
				lcd_send_string("MODE");
				lcd_put_cur(2, 1);
				sprintf(str, "%d", temp[0] / 1000);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				lcd_send_string("2");
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)){
				status = MAN_YEL;
				clearLed();
				setTimer(0, BLINK_TIME);
			}
			else if(isButtonPressed(1)){
				temp[0] += 1000;
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(2)){
				red_time = temp[0];
				setTimer(0, 0);
				displayLed(RED);
				displayLed2(RED);
			}

			break;

		case MAN_YEL:
			if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);

				setTimer(0, BLINK_TIME);
			}
			if (isTimerExpired(1)) {
				lcd_clear();
				lcd_put_cur(0, 0);
				lcd_send_string("VAL_YEL");
				lcd_put_cur(8, 1);
				lcd_send_string("MODE");
				lcd_put_cur(2, 1);
				sprintf(str, "%d", temp[1] / 1000);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				lcd_send_string("3");
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)){
				status = MAN_GREEN;
				clearLed();
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(1)){
				temp[1] += 1000;
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(2)){
				yel_time = temp[1];
				setTimer(0, 0);
				displayLed(YEL);
				displayLed2(YEL);
			}
			break;

		case MAN_GREEN:
			if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				setTimer(0, BLINK_TIME);
			}
			if (isTimerExpired(1)) {
				lcd_clear();
				lcd_put_cur(0, 0);
				lcd_send_string("VALGREEN");
				lcd_put_cur(8, 1);
				lcd_send_string("MODE");
				lcd_put_cur(2, 1);
				sprintf(str, "%d", temp[2] / 1000);
				lcd_send_string(str);
				lcd_put_cur(10, 0);
				lcd_send_string("4");
				setTimer(1, 1000);
			}
			if(isButtonPressed(0)){
				status = INIT;
			}else if(isButtonPressed(1)){
				temp[2] += 1000;
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(2)){
				green_time = temp[2];
				setTimer(0, 0);
				displayLed(GREEN);
				displayLed2(GREEN);
			}
			break;

		default:
				break;
		}
}
