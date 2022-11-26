#include<iostream>
#include<fstream>
#include<cmath>

int main(int argc, char** argv) {
	const int width(atoi(argv[1])), height(atoi(argv[2])), radius(atoi(argv[3]));

	#define IMAGE(x,y) image[x*height+(y)]
	char image[width*height];

	for (int y=0; y<height; y++){
		for (int x=0; x<width; x++){
		IMAGE(x,y) = '0';
		}
	}

	const int center_x=width/2, center_y=width/2;

	for (int y=0; y<height; y++){
		for (int x=0; x<width; x++){
		double distance = std::pow(x - center_x,2)+std::pow(y - center_y,2);
		if (distance<std::pow(radius,2))
			IMAGE(x,y) = '1';
		}
	}

std::ofstream out;
out.open ( "a_circle.pbm", std::ios::out );
out << "P1 " << width << " " << height << std::endl;
out.write ( image, height*width*sizeof(char) );
out.close();

}
