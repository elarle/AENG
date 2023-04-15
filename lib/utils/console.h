#ifndef console
#define console

#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <string>
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

#define cls() puts("\x1B[2J")

#define mv(X, Y) printf("\033[%d;%dH", Y, X)

void Dimensions(int *cols, int *rows);

inline void Dimensions(int *cols, int *rows){

	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	*cols = size.ws_col;
	*rows = size.ws_row;

}

void print(std::string color, std::string msg, ...);
inline void print(std::string color, std::string msg, ...){
	va_list s_args;
	va_start(s_args, msg);
	std::string ap = color;
	ap += msg;
	ap += NORMAL;
	vprintf(ap.c_str(), s_args);
}
void println(std::string color, std::string msg, ...);
inline void println(std::string color, std::string msg, ...){
	va_list s_args;
	va_start(s_args, msg);
	std::string ap = color;
	ap += " " + msg + " ";
	ap += NORMAL;
	ap += '\n';
	vprintf(ap.c_str(), s_args);
}

void println(std::string msg, ...);
inline void println(std::string msg, ...){
	va_list s_args;
	va_start(s_args, msg);
	std::string ap = NORMAL;
	ap += " " + msg + " ";
	ap += NORMAL;
	ap += '\n';
	vprintf(ap.c_str(), s_args);
}

class LoadingBar{
	int length = 50;
	int last = 0;
	public: LoadingBar(int width){
		int sw; int sh;
		Dimensions(&sw, &sh);
		float b = (float)sw/(float)length;
		mv(10, 20);
		//printf("%f", b);
		if(b < 1.0f)length = (int)(length*b)-6;
	}
	public: void setPercentage(int percent, int line){
		if(percent != last){
			char txt[length+2];
			txt[0] = '['; txt[length+1] = ']';
			for(int i = 1; i < length+1; i++){
				txt[i] = '-';
			}
			for(int i = 1; i < ((length+1)/100.)*percent; i++){
				txt[i] = '#';
			}
			mv(0, line);
			print(txt, WHITE);
			mv(length+3, line);
			println((std::to_string(percent))+"%", GREEN);
		}
		last = percent;
	}
};
#endif