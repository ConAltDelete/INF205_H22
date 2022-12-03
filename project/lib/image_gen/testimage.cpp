#include<iostream>
#include<sys/time.h>
#include"image.h"

int ranged_rand (int range, int offset){
	struct timeval timenow;
	gettimeofday (&timenow, NULL);
	srand(timenow.tv_usec);

	int random_number = (rand() % range + offset);
        return(random_number);
}

int main(){

	image my_image(400, 400);

	for (int i=0;i<10;i++){
		my_image.circle(ranged_rand(200,0),ranged_rand(200,0),ranged_rand(20,2),'1');
		my_image.circle(ranged_rand(200,0),ranged_rand(200,0),ranged_rand(20,2),'0');
	}

	my_image.save("image.pbm");

	return(EXIT_SUCCESS);

}
