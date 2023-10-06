#include <stdio.h>
#include <unistd.h>
#include <termios.h>
using namespace std;

#ifndef TELEOP_H
#define TELEOP_H


class getControl {
	public:
		double getX();
		double getZ();
		bool getdoMove();
		void control();
	private:
		char getch();
};
#endif //TELEOP_H 
