#include<iostream>
#include<fstream>
#include<sys/time.h>
#include<cmath>

// Random number function
int ranged_rand (int range, int offset) {
        struct timeval timenow;
        gettimeofday (&timenow, NULL);
        srand(timenow.tv_usec);

        int random_number = (rand() % range + offset);
//        printf("%d\n", random_number);
        return(random_number);
}

int main(int argc,char** argv) {
	// Definitions
	const int
		width(atoi(argv[1])),
		height(atoi(argv[2])),
		radius(ranged_rand(300,100));

	// Macro that says "I'm an image, I have pixels."
	#define IMAGE(x,y) image[x*height+(y)]
	char image[width*height];

	// Fill image with white
	for (int y=0; y<height; y++){
		for (int x=0; x<width; x++){
		IMAGE(x,y) = '0';
		}
	}

	// Define circle origo
	const int center_x=ranged_rand(0,width), center_y=ranged_rand(0,height);

	// Draw the circle
	for (int y=0; y<height; y++){
		for (int x=0; x<width; x++){
		double distance = std::pow(x - center_x,2)+std::pow(y - center_y,2);
		if (distance<std::pow(radius,2))
			IMAGE(x,y) = '1';
		}
	}

	// Save the circle
	std::ofstream out;
	out.open ( "a_circle.pbm", std::ios::out );
	out << "P1 " << width << " " << height << std::endl;
	out.write ( image, height*width*sizeof(char) );
	out.close();

}