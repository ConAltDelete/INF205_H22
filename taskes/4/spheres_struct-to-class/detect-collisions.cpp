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
      std::cin >> spheres[i].get_size();
      for(int d = 0; d < 3; d++) std::cin >> spheres[i].get_coords()[d];
   }

   /*
    * how many collisions are there between the spheres?
    *
    * note: collision here means "overlap" between spheres
    */
   int num_collisions = count_collisions(N, spheres);
   std::cout << num_collisions << " collisions were found.\n";

   /*
    * deallocate the array that was created with "new"
    */
   delete[] spheres;
}
