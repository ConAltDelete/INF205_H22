#ifndef COLLISIONS_STRUCT_H
#define COLLISIONS_STRUCT_H
#include <algorithm>
class Sphere
{
	float size = 0.0;
	float coords[3] = {0.0, 0.0, 0.0};

	public:
	float get_size(){return this->size;}
	float* get_coords(){return this->coords;}
	void set_size(float s){this->size=s;}
	
	void set_coords(float x,float y,float z){
		float new_val[3] = {x,y,z};
		std::copy(new_val,new_val+3,this->coords);
	}

};

/*
struct Sphere
{
   float size = 0.0;
   float coords[3] = {0.0, 0.0, 0.0};
};
*/

/*
 * computes and returns the number of collisions among pairs of N spheres in three dimensions
 * spheres[0], ..., spheres[N-1] are all the Sphere objects
 */
int count_collisions(int N, Sphere* spheres[]);

/*
 * is there a collision between spheres i and j?
 * this helper function, which may also be called directly from outside, determines it
 */
bool check_collision(Sphere* sphere_i, Sphere* sphere_j);

#endif
