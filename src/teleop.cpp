#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "project-1/teleop.h"
using namespace std;

bool doMove;
double x;
double z;

double getControl::getX(){
	return x;
}

double getControl::getZ(){
	return z;
}

bool getControl::getdoMove(){
	return doMove;
}	

char getControl::getch() {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void getControl::control(){   
    char option = ' ';

    while (true)
    {
	option = getch();

	if(option == 'i'){
		x = 1.0; //move the robot forwards
		z = 0.0;
		doMove = true;
	}
	else if(option == 'k'){
		x = -1.0; //move the robot forwards
		z = 0.0;
		doMove = true;
	}
	else if(option == 'j'){
		x = 0.0; //move the robot forwards
		z = 1.0;
		doMove = true;
	}
	else if(option == 'l'){
		x = 0.0; //move the robot forwards
		z = -1.0;
		doMove = true;
	}else{
		doMove = false;
	}
    }
}
