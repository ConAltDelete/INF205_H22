#include "collisions_struct.h"
#include <cmath>
// is there a collision between sphere i and sphere j?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//
//for (int i=0;i<3;i++){array[i]=newValue[i]}
//void set_coords()={this->coords={x,y,z};}

bool check_collision(Sphere* sphere_i, Sphere* sphere_j)
{
   /*
    * vector pointing from the centre of i to the centre of j
    */
	float sphere_j_coords[3];
	for(int i = 0; i < 3; i++) sphere_j_coords[i] = sphere_j->get_coords()[i];
	float sphere_i_coords[3];sphere_j->get_coords();
	for(int i = 0; i < 3; i++) sphere_i_coords[i] = sphere_i->get_coords()[i];

   float distance_vector[3] = {
	   std::abs(sphere_j_coords[0] - sphere_i_coords[0]),
      std::abs(sphere_j_coords[1] - sphere_i_coords[1]),
      std::abs(sphere_j_coords[2] - sphere_i_coords[2])
   };

   /*
    * square distance between the centre of i and the centre of j
    */
   float square_distance = 0.0;
   for(int d = 0; d < 3; d++)
      square_distance += distance_vector[d]*distance_vector[d];

   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   float sum_of_radii = 0.5 * (sphere_i->get_size() + sphere_j->get_size());
   return square_distance < sum_of_radii*sum_of_radii;
}

// count the number of collisions between pairs of spheres
//
int count_collisions(int N, Sphere* spheres[])
{
   int num_collisions = 0;
   
   /*
    * loop going from i = 0, j = 1 up to i = N-2, j = N-1, traversing all pairs
    */
   for(int i = 0; i < N-1; i++)
      for(int j = i+1; j < N; j++)
         if(check_collision(spheres[i], spheres[j]))
            num_collisions++;
   
   return num_collisions;
}
