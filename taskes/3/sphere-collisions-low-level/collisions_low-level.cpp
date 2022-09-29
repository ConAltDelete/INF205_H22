#include "collisions_low-level.h"

// is there a collision between sphere i and sphere j?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//


struct Sphere {
   float size;
   float coordx;
   float coordy;
   float coordz;

   int sqdist(*Sphere B){
		return 
			B->coordx*this->coordx +
			B->coordy*this->coordy +
			B->coordz*this->coordz;
   }
}

bool check_collision(
   Sphere A, Sphere B
){
   /*
    * vector pointing from the centre of i to the centre of j
    */
   
   /*
    * square of that vector
    */
   float square_distance = A.sqdist(&B);
   
   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   float sum_of_radii = 0.5*(A.size+B.size);
   return square_distance < sum_of_radii*sum_of_radii;
}

// count the number of collisions between pairs of spheres
//
int count_collisions(int N, Sphere* pop[])
{
   int num_collisions = 0;
   
   /*
    * loop going from i = 0, j = 1 up to i = N-2, j = N-1, traversing all pairs
    */
   for(auto P1: pop)
		for(auto P2 = *pop; P2 < pop.end(); P2 = P2+1!=P1 ? P2+1 : P2+2)
			if(check_collision(*P1,*P2))
            	num_collisions++;
   
   return num_collisions;
}
