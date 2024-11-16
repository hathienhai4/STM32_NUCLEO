/*
 * displayLCD.c
 *
 *  Created on: Nov 16, 2024
 *      Author: admin
 */
#include<displayLCD.h>


void displayLCD1(int number, char *string){
	char str[16];
	int n = (number / 1000) % 100;
	lcd_put_cur(0, 0);
	lcd_send_string(string);

	lcd_put_cur(1, 3);
	snprintf(str, sizeof(str), "%02d", n);
	lcd_send_string(str);
}
void displayLCD2(int number, char * string){
	char str[16];
	int n = (number / 1000) % 100;
	lcd_put_cur(1, 8);
	lcd_send_string(string);

	lcd_put_cur(0, 10);
	snprintf(str, sizeof(str), "%02d", n);
	lcd_send_string(str);
}

void acp(){
	char str[16];
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Successfully ");
	lcd_put_cur(1, 10);
	lcd_send_string("Saved");
}




