#include "image_read.h"

std::vector<coords> read_image(std::string image_path){
	std::ifstream image(image_path);

	std::string header; 
	
	image.getline(file,header); // getting head of file
	

}
