#ifndef ARC_DIC
#define ARC_DIC

#include "coordstruct.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#include "coordstruct.h"

#define PI 2.0*std::acos(0.0)

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
