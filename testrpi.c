#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#include "lcd.h"

int getch (void);

/* 
 * get i2c address -> 	sudo i2cdetect -y 0 - rpi rev 1
 * 						sudo i2cdetect -y 1 - rpi rev 2
 */


#define ADDR 0x3f // i2c Address

int getch (void)
{
        int ch;
        struct termios oldt, newt;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
}

int main(void)
{
    lcdSetup(ADDR, 1);
	/* i2c Address and busnum <- 0 (rev 1) | 1 (rev 2) */
	lcdBacklight(ON);
	lcdClear();

	lcdMessage("LCD Test Line 1\n");
	lcdMessage("Press any Button!");
    return 0;
}