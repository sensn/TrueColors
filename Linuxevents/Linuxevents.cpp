#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <string.h>

#include <assert.h>

//#include<iostream.h>
#include<math.h> // Needed for fmod()
int truecolor();

typedef struct {
	double r;       // ∈ [0, 1]
	double g;       // ∈ [0, 1]
	double b;       // ∈ [0, 1]
} rgb;

typedef struct {
	double h;       // ∈ [0, 360]
	double s;       // ∈ [0, 1]
	double v;       // ∈ [0, 1]
} hsv;
// HSVtoRGB(float fH, float fS, float fV, int output[3]);
rgb hsv2rgb(hsv HSV);

//using namespace std;

/*
 * H(Hue): 0 - 360 degree (integer)
 * S(Saturation): 0 - 1.00 (double)
 * V(Value): 0 - 1.00 (double)
 *
 * output[3]: Output, array size 3, int
 */
int main() {
	int output[3];
	//HSVtoRGB(231, 1, 1, output);

	int ch, count = 0;
	MEVENT event;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	clear();
	cbreak();

	getch();
	hsv hesv;
	hesv.h = 1.0;
	hesv.s = 0.5;
	hesv.v = 1.0;
	rgb rrgb;

	for (int i = 0; i < 360; i += 1) {
		//printf ("%d\n",i);
		//HSVtoRGB((float)i, 0.7, 0.5, output);
		hesv.h = (double)i;
		rrgb = hsv2rgb(hesv);

		//printf ("%lf ;%lf ;%lf \n",rrgb.r*255,rrgb.g*255,rrgb.b*255);
		//printf ("%d ;%d ;%d \n",output[0],output[1],output[2]);
		printf("\x1b[38;2;%d;%d;%dmTRUECOLOR\x1b[0m\n", (int)rrgb.b * 255, (int)rrgb.g * 255, (int)rrgb.r * 255);
		//printf ("\033[%d;%dH\x1b[38;2;%d;%d;%dmTRUECOLOR\x1b[0m\n",i, 5,output[0],output[1],output[2]);
	}
	getch();
	//getch();
	//exit(0);
	//truecolor();
	getch();
	//printf ("\033[2J"); //clr

   // system("pause");
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events


	while ((ch = getch()) != 'q')
	{
		count++;
		// mvprintw(1, 1, "Has mouse: %d", has_mouse());
		// mvprintw(2, 1, "Key code: %x; mouse code:%x", ch, KEY_MOUSE);

		if (ch == KEY_MOUSE)
		{
			//       snprintf(buffer, max_size, "Mouse at row=%d, column=%d bstate=0x%08lx",
							 //event.y, event.x, event.bstate);
			printf("\033[2J");

			assert(getmouse(&event) == OK);
			wmove(stdscr, 5, 10);
			truecolor();
			/*  mvprintw(event.y,event.x,"~");

				mvprintw(3, 3, "Muse Event: x=%d, y=%d z=%d",
						 event.x, event.y, event.z);
				mvprintw(4, 3, "Mouse device id: %x", event.id);
				mvprintw(5, 3, "Mouse button mask: %x", event.bstate);
				*/
		}
		//mvprintw(6, 1, "Event number: %4d",count);
		printf("\033[%d;%dH\x1b[38;2;%d;%d;%dmTRUECOLOR\x1b[0m\n", event.y, event.x, output[0], output[1], output[2]);
		// printf ("\033[%d;%dH\x1b[38;2;255;100;100mTRUECOLOR\x1b[0m\n",event.y, event.x);
		refresh();
	}
	endwin();
}

int truecolor() {
	int r = 25;
	int g = 55;
	int b = 99;
	// printf("\x1b[38;2;255;100;100m%d %d %"1,1,r,g,b);
	for (int colnum = 0; colnum < 77; colnum++) {
		r = 255 - (colnum * 255 / 76);
		g = (colnum * 510 / 76);
		b = (colnum * 255 / 76);
		if (g > 255) g = 510 - g;
		printf("%d %d %d", r, g, b);
		printf("\033[%d;%dH\x1b[38;2;%d;%d;%dmTRUECOLOR\x1b[0m\n", colnum, 1, r, g, b);
		//printf ("\x1b[48;2;%d;%d;%dmTRUECOLOR%d\n", r,g,b,r);
		printf("\033[38;2;%d;%d;%dm", 255 - r, 255 - g, 255 - b);
	}
	getch();
	return 9;
}




rgb hsv2rgb(hsv HSV)
{
	rgb RGB;
	double H = HSV.h, S = HSV.s, V = HSV.v,
		P, Q, T,
		fract;

	(H == 360.) ? (H = 0.) : (H /= 60.);
	fract = H - floor(H);

	P = V * (1. - S);
	Q = V * (1. - S * fract);
	T = V * (1. - S * (1. - fract));

	if (0. <= H && H < 1.)
		RGB = (rgb){ .r = V, .g = T, .b = P };
	else if (1. <= H && H < 2.)
		RGB = (rgb){ .r = Q, .g = V, .b = P };
	else if (2. <= H && H < 3.)
		RGB = (rgb){ .r = P, .g = V, .b = T };
	else if (3. <= H && H < 4.)
		RGB = (rgb){ .r = P, .g = Q, .b = V };
	else if (4. <= H && H < 5.)
		RGB = (rgb){ .r = T, .g = P, .b = V };
	else if (5. <= H && H < 6.)
		RGB = (rgb){ .r = V, .g = P, .b = Q };
	else
		RGB = (rgb){ .r = 0., .g = 0., .b = 0. };

	return RGB;
}







int
main2()
{
	int ch;

	initscr();
	raw();
	noecho();
	cbreak();
	refresh();
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	while (1)
	{
		ch = getch();
		addch(ch);
		keypad(stdscr, TRUE);
		MEVENT event;
		switch (ch)
		{
		case KEY_UP:
			printf("keyup");
			break;
		case KEY_DOWN:
			printf("keydown");
			break;
		case KEY_MOUSE:
			if (getmouse(&event) == OK)
			{
				if (event.bstate & BUTTON1_PRESSED) // This works for left-click
				{
					printf("button1");
				}
				else if (event.bstate & BUTTON2_PRESSED) // This doesn't capture right-click
				{
					printf("button2");
				}
				else
					printf("Event: %i", event.bstate); // Doesn't print anything on right-click
			}
			break;
		}
	}
	return 0;
}













int main1(int argc, char** argv) {

	while (1)
	{
		keypad(stdscr, TRUE);
		mousemask(ALL_MOUSE_EVENTS, NULL);

		int c = getch();
		keypad(stdscr, TRUE);
		MEVENT event;
		switch (c)
		{
		case KEY_UP:
			printf("keyup");
			break;
		case KEY_DOWN:
			printf("keydown");

			break;
		case KEY_MOUSE:
			if (getmouse(&event) == OK)
			{
				if (event.bstate & BUTTON1_PRESSED) // This works for left-click
				{
					printf("button1");
				}
				else if (event.bstate & BUTTON2_PRESSED) // This doesn't capture right-click
				{
					printf("button2");
				}
				else
					printf("Event: %i", event.bstate); // Doesn't print anything on right-click
			}
			break;
		}
	}
	return 0;
}
