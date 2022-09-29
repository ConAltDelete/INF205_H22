#include <stdint.h>
#include <iostream>
#include "timing.h"

bool is_prime(int64_t n)
	// Figuring out if number N is a prime number
{
   for(int64_t i = 2; n >= i*i; i++)
   {
      if((n % i) == 0) return false;
   }
   return true;
}

int main(int argn, char** argv){
 	/*
  	* simualting n^1/2 with testing
  	* */
	int test = 100;

	std::cout << "best case: " << best_case(*is_prime, test) << "\n";
	std::cout << "avg case: " << avg_case(*is_prime, test) << "\n";
	//std::cout << "worst case: " << worst_case(*is_prime, test) << "\n";
}
