/*
 * RYG_LED.c
 *
 *  Created on: Nov 14, 2024
 *      Author: admin
 */
#include <RYG_LED.h>

void clearLed(){
	displayLed(-1);
	displayLed2(-1);
}

void displayLed(int state){
	switch(state){
		case RED:
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
			break;
		case YEL:
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
			break;
		case GREEN:
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
			break;
		default:
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
			break;
	}
}
void displayLed2(int state){
	switch(state){
		case RED:
			HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
			break;
		case YEL:
			HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
			break;
		case GREEN:
			HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
			break;
		default:
			HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
			break;
	}
}
