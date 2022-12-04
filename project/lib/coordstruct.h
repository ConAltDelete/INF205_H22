#ifndef VIEW_CIRC
#define VIEW_CIRC

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Circle {
	int x;
	int y;
	float R;
};

void draw_circle(std::vector<Circle> data);

#endif
