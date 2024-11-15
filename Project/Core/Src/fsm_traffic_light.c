/*
 * fsm_traffic_light.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#include "fsm_traffic_light.h"


void checkTime(){
	if(red_time != yel_time + green_time){
		red_time = yel_time + green_time;
	}
}

void fsm_traffic(){
	switch(status){
		case INIT:
			checkTime();
			status = RED_GREEN;
			setTimer(0,green_time);
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case RED_GREEN:
			displayLed(RED);
			displayLed2(GREEN);
			if(isTimerExpired(0)){
				status = RED_YEL;
				setTimer(0,yel_time);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case RED_YEL:
			displayLed(RED);
			displayLed2(YEL);
			if(isTimerExpired(0)){
				status = GREEN_RED;
				setTimer(0, green_time);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;
		case GREEN_RED:
			displayLed(GREEN);
			displayLed2(RED);
			if(isTimerExpired(0)){
				status = YEL_RED;
				setTimer(0, yel_time);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;
		case YEL_RED:
			displayLed(YEL);
			displayLed2(RED);
			if(isTimerExpired(0)){
				status = RED_GREEN;
				setTimer(0, green_time);
			}
			if(isButtonPressed(0)) status = MAN_INIT;
			break;

		case MAN_INIT:
			setTimer(0,BLINK_TIME);
			status = MAN_RED;
			init_Button(1);
			init_Button(2);
			clearLed();
			temp[0] = red_time;
			temp[1] = yel_time;
			temp[2] = green_time;
			break;
		case MAN_RED:
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
			else if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
				setTimer(0, BLINK_TIME);
			}
			break;

		case MAN_YEL:
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
			else if(isTimerExpired(0)){
				HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);

				setTimer(0, BLINK_TIME);
			}
			break;

		case MAN_GREEN:
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
