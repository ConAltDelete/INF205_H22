#ifndef ARC_DIC
#define ARC_DIC

#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include<algorithm>

#define PI 2.0*std::arccos(0.0)

struct coords{
	int x;
	int y;

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
};

float arc_radius(float H, float W);
float radius_detect(coords A, coords B, coords P);
float w(int x, int y);
float I(bool x_dir, std::vector<coords> c);
std::vector<coords> get_neighborhood(std::vector<coords> contour, int index, int size);
std::vector<coords> get_neighborhood(std::vector<coords> contour, int index, int size, int &back_ref, int &front_ref);
float quad_solve(bool pos, float points[4]);
std::vector<float> A_eigen(std::vector<coords> c);
std::vector<int> find_corners(std::vector<coords> blob, float limit);
coords cal_center(coords A, coords B,coords P);
std::vector<Circle> find_circles(std::vector<coords> blob, float limit);

#endif
