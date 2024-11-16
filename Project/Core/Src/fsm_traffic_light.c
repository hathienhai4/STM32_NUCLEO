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
	temp[0] = red_time;
	temp[2] = yel_time;
	temp[1] = green_time;
}


void fsm_traffic(){
	switch(status){
		case INIT:
			checkTime();
			status = RED_GREEN;
			setTimer(0,green_time);
			if(isButtonPressed(0)) status = MAN_INIT;
			setTimer(0, green_time);
			setTimer(1, 1000);
			lcd_clear();
			break;

		case RED_GREEN:
			val1 = timer_counter[0] * 10 + yel_time;
			val2 = timer_counter[0] * 10;
			displayLed(RED);
			displayLed2(GREEN);
			displayLCD1(val1, "RED");
			displayLCD2(val2, "GREEN");
			if(isTimerExpired(0)){
				status = RED_YEL;
				val1 = 0;
				val2 = 0;
				setTimer(0,yel_time);
				lcd_clear();
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case RED_YEL:
			val1 = timer_counter[0] * 10;
			val2 = timer_counter[0] * 10;
			displayLed(RED);
			displayLed2(YEL);
			displayLCD1(val1, "RED");
			displayLCD2(val2, "YELLOW");

			if(isTimerExpired(0)){
				status = GREEN_RED;
				val1 = 0;
				val2 = 0;
				setTimer(0, green_time);
				lcd_clear();
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;
		case GREEN_RED:
			val2 = timer_counter[0] * 10 + yel_time;
			val1 = timer_counter[0] * 10;
			displayLed(GREEN);
			displayLed2(RED);
			displayLCD1(val1, "GREEN");
			displayLCD2(val2, "RED");
			if(isTimerExpired(0)){
				status = YEL_RED;
				val1 = 0;
				val2 = 0;
				setTimer(0, yel_time);
				lcd_clear();
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;
		case YEL_RED:
			val2 = timer_counter[0] * 10;
			val1 = timer_counter[0] * 10;
			displayLed(YEL);
			displayLed2(RED);
			displayLCD1(val1, "YELLOW");
			displayLCD2(val2, "RED");
			if(isTimerExpired(0)){
				status = RED_GREEN;
				val1 = 0;
				val2 = 0;
				setTimer(0, green_time);
				lcd_clear();
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case MAN_INIT:
			setTimer(0,BLINK_TIME);
			status = MAN_RED;
			init_Button(1);
			init_Button(2);
			clearLed();
			lcd_clear();
			red_time = temp[0];
			green_time = temp[1];
			yel_time = temp[2];
			break;
		case MAN_RED:
			displayLCD1(2000, "MODE");
			displayLCD2(temp[0], "RED");
			if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
				setTimer(0, BLINK_TIME);
			}
			if(isButtonPressed(0)){
				status = MAN_YEL;
				clearLed();
				setTimer(0, BLINK_TIME);
			}
			else if(isButtonPressed(1)){
				temp[0] += 1000;
				if (temp[0] >= 100000) temp[0] = 1000;
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(2)){
				acp();
				HAL_Delay(500);lcd_clear();
				displayLCD1(2000, "MODE");
				displayLCD2(temp[0], "RED");
				red_time = temp[0];
				setTimer(0, 0);
				displayLed(RED);
				displayLed2(RED);
			}
			else if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
				setTimer(0, BLINK_TIME);
			}
			break;

		case MAN_YEL:
			displayLCD1(3000, "MODE");
			displayLCD2(temp[1], "AMBER");
			if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);

				setTimer(0, BLINK_TIME);
			}
			if(isButtonPressed(0)){
				status = MAN_GREEN;
				clearLed();
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(1)){
				temp[1] += 1000;
				if (temp[1] >= 100000) temp[1] = 1000;
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(2)){
				acp();
				HAL_Delay(500);
				lcd_clear();
				displayLCD1(3000, "MODE");
				displayLCD2(temp[1], "AMBER");
				yel_time = temp[1];
				setTimer(0, 0);
				displayLed(YEL);
				displayLed2(YEL);
			}
			else if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);

				setTimer(0, BLINK_TIME);
			}
			break;

		case MAN_GREEN:
			displayLCD1(4000, "MODE");
			displayLCD2(temp[2], "GREEN");
			if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				setTimer(0, BLINK_TIME);
			}
			if(isButtonPressed(0)){
				status = INIT;
			}else if(isButtonPressed(1)){
				temp[2] += 1000;
				if (temp[2] >= 100000) temp[2] = 1000;
				setTimer(0, BLINK_TIME);
			}else if(isButtonPressed(2)){
				acp();
				HAL_Delay(500);lcd_clear();
				displayLCD1(4000, "MODE");
				displayLCD2(temp[2], "GREEN");
				green_time = temp[2];
				setTimer(0, 0);
				displayLed(GREEN);
				displayLed2(GREEN);
			}
			else if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				setTimer(0, BLINK_TIME);
			}
			break;

		default:
				break;
		}
}
