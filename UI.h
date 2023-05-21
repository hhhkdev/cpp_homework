#ifndef UI_H
#define UI_H

#include <string>
using namespace std;

class UI {
public:
	static int getMainMenu();
	static int getShapeType();
	static int getShapeIndex();
	static void println(string);
	static void print(string);
	static void print(int);
};

#endif