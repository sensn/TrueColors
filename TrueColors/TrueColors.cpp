#include "fast_hsv2rgb.h"
#include <stdio.h>
#include <iostream>

const unsigned PIN_RED = 3;
const unsigned PIN_GRN = 5;
const unsigned PIN_BLU = 6;

uint16_t hue;
uint8_t  val;
int8_t   dir;
uint8_t  prevtime;

void setup()
{
	//pinMode(PIN_RED, OUTPUT);	// Red PWM output
	//pinMode(PIN_GRN, OUTPUT);	// Green PWM output
	//pinMode(PIN_BLU, OUTPUT);	// Blue PWM output
	hue = HSV_HUE_MIN;
	val = HSV_VAL_MAX;
	dir = -3;
//	prevtime = millis();
}

void main()
{
	setup();
	uint8_t r, g, b;
//	uint8_t now = millis();
//	uint8_t tdiff = now - prevtime;
	//std::cin.get();
	for (int i = 0; i < 255*6; i+=6) {

		//if (tdiff >= 5) {
		//	prevtime = now;		// Change color every 5ms

		//hue++;			// Increase hue to circle and wrap
		//if (hue > HSV_HUE_MAX)
		//	hue -= HSV_HUE_MAX;

		//val += dir;		// Vary value between 1/4 and 4/4 of HSV_VAL_MAX
		//if (val < HSV_VAL_MAX / 4 || val == HSV_VAL_MAX)
		//	dir = -dir;	// Reverse value direction

		// Perform conversion at fully saturated color
		//fast_hsv2rgb_32bit(hue, HSV_SAT_MAX, val, &r, &g, &b);
		//fast_hsv2rgb_32bit(i, i/6, i / 6, &r, &g, &b);
		fast_hsv2rgb_32bit(i, 255, 255, &r, &g, &b);
		//fast_hsv2rgb_32bit(i, HSV_SAT_MAX, 255, &r, &g, &b);

		// Write new color to PWM outputs
		// Use ~r, ~g and ~b when using common-anode LEDs
	/*	analogWrite(PIN_RED, r);
		analogWrite(PIN_GRN, g);
		analogWrite(PIN_BLU, b);*/
		//printf("\033[%d;%dH\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dmTRUECOLORS\x1b[0m\n",i,7, r,g,b, r, g, b, i/6);    //mit Pos
		printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dmTRUECOLORS\x1b[0m\n", r,g,b, r, g, b, i/6);
		//printf("\x1b[38;2;%d;%d;%dmTRUECOLORS\x1b[0m\n", r,g,b,i/6);
		//printf("\x1b[38;2;%d;%d;%dmTRUECOLORS%d\x1b[0m\n", r,g,b,i/6);
			//}
	}
}