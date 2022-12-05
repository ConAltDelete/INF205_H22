#include "coordstruct.h"

int main() {
	std::vector<Circle> data = {
		Circle{100,100,10},
		Circle{150,50,5}
	};

	draw_circle(data);


	return 0;
}
