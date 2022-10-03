#include <iostream>
#include "collisions_struct.h"

int main()
{
   int N = 0; // N will be the number of spheres
   std::cin >> N;  // input number of spheres

   /*
    * array containing all the spheres
    */
   Sphere* spheres = new Sphere[N]();

   /*
    * read all the data from standard input
    */
   for(int i = 0; i < N; i++)
   {
	   float e;
      std::cin >> e;
	  spheres[i].set_size(e);
	  float coord[3];
      for(int d = 0; d < 3; d++){
		  std::cin >> coord[d];
	  }
	  spheres[i].set_coords(coord[0],coord[1],coord[2]);
   }

   /*
    * how many collisions are there between the spheres?
    *
    * note: collision here means "overlap" between spheres
    */
   int num_collisions = count_collisions(N, &spheres);
   std::cout << num_collisions << " collisions were found.\n";

   /*
    * deallocate the array that was created with "new"
    */
	delete[] spheres;
}
