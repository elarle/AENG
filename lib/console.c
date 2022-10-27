#ifndef AENG_CONSOLE
#define AENG_CONSOLE

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define NORMAL  "\x1B[0m"
#define RED  "\x1B[1;31m"
#define GREEN  "\x1B[1;32m"
#define YELLOW  "\x1B[1;33m"
#define BLUE  "\x1B[1;34m"
#define MAGENTA  "\x1B[1;35m"
#define CYAN  "\x1B[1;36m"
#define WHITE  "\x1B[1;37m"

#define BNORMAL  "\x1B[0m"
#define BRED  "\x1B[0;31m"
#define BGREEN  "\x1B[0;32m"
#define BYELLOW  "\x1B[0;33m"
#define BBLUE  "\x1B[0;34m"
#define BMAGENTA  "\x1B[0;35m"
#define BCYAN  "\x1B[0;36m"
#define BWHITE  "\x1B[0;37m"

#define BGNORMAL "\x1B[40m"
#define BGRED " \x1B[41m"
#define BGGREEN "\x1B[42m"
#define BGYELLOW "\x1B[43m"
#define BGBLUE "\x1B[44m"
#define MBMAGENTA "\x1B[45m"
#define BGCYAN "\x1B[46m"
#define BGWHITE "\x1B[47m"

#define clean() puts("\x1B[2J")

#define mv(X, Y) printf("\033[%d;%dH", Y, X)

void Dimensions(int *cols, int *rows);

#define altS() puts("\033[?1049h\033[H")
#define altSEx() puts("\033[?1049l")

void echoOff();
void echoOn();

void Dimensions(int *cols, int *rows){

	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	*cols = size.ws_col;
	*rows = size.ws_row;

}//tec_get_cols_rows*/

void echoOff(){

	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);

}//tc_echo_off*/

void echoOn(){

	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ECHO;
	tcsetattr(1, TCSANOW, &term);

}//tc_echo_on*/

#endif