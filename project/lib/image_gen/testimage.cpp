#include<iostream>
#include<sys/time.h>
#include"image.h"

int ranged_rand (int range, int offset){
	struct timeval timenow;
	gettimeofday (&timenow, NULL);
	srand(timenow.tv_usec);
}

int main(){

	image my_image(200, 200);

	my_image.circle(100,100,50);

	my_image.save("image.pbm");

	return(EXIT_SUCCESS);

}
