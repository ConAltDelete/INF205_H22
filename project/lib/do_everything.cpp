#include "coordstruct.h"
#include "read_image2.cpp"
#include "edge_detection.cpp"
#include "ARCDIC.cpp"
#include "view_circles.cpp"

int main(){

	coords zero {15,15};
	coords not_zero {16,15};

	std::vector<coords> image_binary = read_file("image.pbm");			// read_image2.cpp
	std::vector<coords> img_contour = contour(image_binary,zero,not_zero);		// edge_detection.cpp
	std::vector<Circle> circles = find_circles(img_contour,1.0);			// ARCDIC.cpp
	draw_circle(circles);								// view_circles.cpp

}
