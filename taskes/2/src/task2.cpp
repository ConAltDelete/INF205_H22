#include "PNG.cpp"

bool is_prime(int64_t n)
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
	
}
