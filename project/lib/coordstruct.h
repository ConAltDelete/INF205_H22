#ifndef HEADER_GUARD
#define HEADER_GUARD

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

struct coords{
	int x;
	int y;

	// Little tool to check whether I exist
	bool operator==(coords const &a){
		return (this->x == a.x) && (this->y == a.y);
	}

	coords operator+(coords const &a){
		return coords{this->x + a.x,this->y + a.y};
	}

	coords operator-(coords const &a){
		return coords{this->x - a.x,this->y - a.y};
	}
};

struct Circle {
	int x;
	int y;
	float R;
	int colour = 0;
};


/*
 *	gets the next clockwise diraction based on two points A, and B.
 * */
coords get_next_dir(coords A, coords B);

/*
 * traverses through the image until it hits a pixel not equal to the background. Then it looks clockwise/anti-clockwise from the previus pixle in the Moore Neighborhood until it finds a new point, and then creates a new Moore neighborhood. This continues until it findes the original point.
 */
std::vector<coords> contour(std::vector<coords> image, coords start_point, coords pre_point);

std::vector<coords> read_image(std::string image_path);

void draw_circle(std::vector<Circle> data);

#endif
