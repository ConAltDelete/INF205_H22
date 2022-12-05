#include "ARCDIC.h"


float arc_radius(float H, float W) {
	return (W / (8*H) + H/2);
}

float radius_detect(coords A, coords B, coords P) {
	coords diff = B-A;
	float bredde = std::sqrt(diff.x*diff.x + diff.y*diff.y);
	
	float d = 1/bredde;

	float høyde = std::abs((B.x-A.x)*(A.y-P.y) - (A.x-P.x)*(B.y - A.y))*d;

	return arc_radius(høyde, bredde);
}

float w(int x, int y) {
	float scale = 1/(2*PI);
	float p = std::exp(-(x*x + y*y)/2);
	return scale*p;
}


float I(bool x_dir, std::vector<coords> c) {
	/*if(x_dir){
		auto f = [](int a,int b){return a+3*b;};
	} else {
		auto f = [](int a, int b){return b+3*a;};
	}*/

	coords center = c[(c.size()-1)/2];

	int soble_array[] = {
		1,2,1,0,0,0,-1,-2,-1
	};

	float deriv = 0;

	for(int j = -1; j < 2; j++){
		for(int i = -1; i < 2; i++){
			if(std::find(c.begin(), c.end(), coords{i+center.x,j+center.y}) == c.end()){
				continue;
			}
			if(x_dir){
				deriv += soble_array[i+1+3*j+3];
			} else {
				deriv += soble_array[j+1+3*i+3];
			}
		}
	}

	return deriv;
}

std::vector<coords> get_neighborhood(std::vector<coords> contour, int index, int size) {
	int back = index, front = index;
	bool back_found = false, front_found = false; 
	
	int search_area = 0;
	coords attempt;

	double break_limit = std::sqrt(2)*size;

	while(!back_found || !front_found) {
		if(!back_found){
			back--;
			attempt = contour[back<0 ? contour.size() - back : back];
			if( std::sqrt(attempt.x*attempt.x + attempt.y*attempt.y) > break_limit ){
				back++;
				back_found = true;
			}
		}
	
		if(!front_found){
			front++;
			attempt = contour[front>contour.size() ? front - contour.size() : front];
			if( std::sqrt(attempt.x*attempt.x + attempt.y*attempt.y) > break_limit ){
				front--;
				front_found = true;
			}
		}
	}
	back = back<0 ? contour.size() - back : back;
	front = front >= contour.size() ? front - contour.size() : front;

	std::vector<coords> hood;
	for(int i = std::min(back,front); i <= std::max(front,back); i++) hood.push_back(contour[i]);

	return hood;
}

std::vector<coords> get_neighborhood(std::vector<coords> contour, int index, int size, int &back_ref, int &front_ref) {
	int back = index, front = index;
	bool back_found = false, front_found = false; 
	
	int search_area = 0;
	coords attempt;

	double break_limit = std::sqrt(2)*size;

	while(!back_found || !front_found) {
		if(!back_found){
			back--;
			attempt = contour[back<0 ? contour.size() - back : back];
			if( std::sqrt(attempt.x*attempt.x + attempt.y*attempt.y) > break_limit ){
				back++;
				back_found = true;
			}
		}
	
		if(!front_found){
			front++;
			attempt = contour[front>contour.size() ? front - contour.size() : front];
			if( std::sqrt(attempt.x*attempt.x + attempt.y*attempt.y) > break_limit ){
				front--;
				front_found = true;
			}
		}
	}
	back = back<0 ? contour.size() - back : back;
	front = front >= contour.size() ? front - contour.size() : front;

	back_ref = back;
	front_ref = front;

	std::vector<coords> hood;
	for(int i = std::min(back,front); i <= std::max(front,back); i++) hood.push_back(contour[i]);

	return hood;
}

float quad_solve(bool pos, float points[4]){
	float p1 = points[3] + points[0];
	float p2 = points[0]*points[3] + points[1]*points[2];

	float top;
	if(pos){
		top = p1 + std::sqrt(p1*p1-4*p2);
	} else {
		top = p1 - std::sqrt(p1*p1-4*p2);
	}

	return top/2;
}

std::vector<float> A_eigen(std::vector<coords> c /*the entire contour of blob*/) { //! kan ikke bruke float[4]
	/*
	 * The vectors form a 3x3 area
	 * */

	std::vector<coords> c_hood, c_hood_small, c_hood_large;

	float I_x, I_y;
	float l_min,l1,l2;

	std::vector<float> Mat; 

	int back_index, front_index, first_index, last_index;
	
	for(int i = 0; i < c.size(); i++){
		c_hood_small = get_neighborhood(c, i, 1);
		c_hood_large = get_neighborhood(c, i, 2);

		for(int f = 0; f < c_hood_large.size(); f++ ){
			if(c_hood_large[f] == c_hood_small[0]){
				first_index = f;
				break;
			}
		}
		for(int f = c_hood_large.size()-1; f > 0; f-- ){
			if(c_hood_large[f] == *c_hood_small.end()){
				last_index = f;
				break;
			}
		}

		float Is[4];

		for(int j = first_index; j <= last_index; j++){
			c_hood = get_neighborhood(c_hood_large, j, 1);
			I_x = I(true,c_hood);
			I_y = I(false, c_hood);
			Is[0] = I_x*I_x;
			Is[1] = I_y*I_x;
			Is[2] = I_x*I_y;
			Is[3] = I_y*I_y;
		}
		
		l1 = quad_solve(true,Is);
		l2 = quad_solve(false,Is);
		l_min = std::min(l1,l2);

		Mat.push_back(l_min);
	}
	return Mat;
}

std::vector<int> find_corners(std::vector<coords> blob, float limit) {
	/*
	 * returns a vector with indexes for corners.
	 */
	std::vector<float> lambdas =  A_eigen(blob);
	std::vector<int> corners;
	for(int i = 0; i < blob.size(); i++){
		if(lambdas[i] >= limit){
			corners.push_back(i);
		}
	}
	return corners;
}

coords cal_center(coords A, coords B,coords P){
	coords delta_2 = B-A;
	coords delta_3 = P-A;
	double xtop = delta_2.x*delta_2.x*delta_3.y - delta_3.x*delta_3.x*delta_2.y + delta_2.y*delta_2.y*delta_3.y - delta_3.x*delta_3.x*delta_2.y;
	double ytop = delta_2.x*delta_2.x*delta_3.x - delta_3.x*delta_3.x*delta_2.x + delta_2.y*delta_2.y*delta_3.x - delta_3.x*delta_3.x*delta_2.x;

	int xc = A.x + xtop/(2*(delta_2.x*delta_3.y - delta_3.x*delta_2.y));
	int yc = A.x + ytop/(2*(delta_3.x*delta_2.y - delta_2.x*delta_3.y));
	return coords{xc,yc};
}

std::vector<Circle> find_circles(std::vector<coords> blob, float limit){
	std::vector<int> indexes_corners = find_corners(blob,limit);

	coords A,B,P, cent;
	float r;

	std::vector<Circle> ret;

	for(int i = 0; i < indexes_corners.size()-1;i++){
		A = blob[indexes_corners[i]];
		B = blob[indexes_corners[i+1]];
		P = blob[(int)((indexes_corners[i] + indexes_corners[i+1])/2)];
		r = radius_detect(A,B,P);

		cent = cal_center(A,B,P);

		ret.push_back(Circle{cent.x,cent.y,r});
	}
	return ret;
}
