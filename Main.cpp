#include <iostream>
using namespace std;

#include "GraphicEditor.h"

int main() {
	GraphicEditor *g = new GraphicEditor();
	g->run();
	delete g;
}