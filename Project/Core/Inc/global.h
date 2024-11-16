/*
 * global.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"
#include "main.h"
#include "RYG_LED.h"
#include "i2c-lcd.h"
#include <fsm_traffic_light.h>
#include <scheduler.h>
#include <stdio.h>
#include <math.h>
#include <displayLCD.h>

#define TICK 10
#define INIT 1
#define MAN_INIT 9
#define GREEN_RED 2
#define YEL_RED 3
#define RED_GREEN 4
#define RED_YEL 5
#define MAN_RED 6
#define MAN_YEL 7
#define MAN_GREEN 8



extern int status;
extern int red_time;
extern int green_time;
extern int yel_time;
extern int temp[3];

extern int val1;
extern int val2;
extern char str[90];

#endif /* INC_GLOBAL_H_ */
