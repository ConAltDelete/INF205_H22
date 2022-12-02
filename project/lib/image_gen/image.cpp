#include<iostream>
#include<fstream>
#include<cmath>
#include"image.h"

// Constructor
image::image(int width, int height){
	this->pixels = new char[width*height];
	this->width = width;
	this->height = height;

	for (int i = 0; i < (width*height); i++){
		this->pixels[i] = '0';
	}

std::cout<<"Constructor says: Width->"<<width << ", Hight->"<<height<<"\n";
}

// Destructor
image::~image(void){

	delete[] this->pixels;

std::cout<<"Destructor\n";
}

// Set point
void image::set_point (int x, int y, char colour){
	this->pixels[(y * this->width + x)] = colour;
}

// Draw circle
void image::circle (int origin_x, int origin_y, int r){
	int xmin = std::max((origin_x-r),0);
	int ymin = std::max((origin_y-r),0);

	int xmax = std::min((origin_x+r),width);
	int ymax = std::min((origin_y+r),height);

	for (int x=xmin; x<=xmax; x++){
		for (int y=ymin; y<=ymax; y++){

			double d = std::pow(x - origin_x,2)+std::pow(y - origin_y,2);
			if (d<=std::pow(r,2)){
				set_point(x,y,'1');
			}
		}
	}
}
// generate positiv or negative circle
void image::circle (int origin_x, int origin_y, int r, char val){
	int xmin = std::max((origin_x-r),0);
	int ymin = std::max((origin_y-r),0);

	int xmax = std::min((origin_x+r),width);
	int ymax = std::min((origin_y+r),height);

	for (int x=xmin; x<=xmax; x++){
		for (int y=ymin; y<=ymax; y++){

			double d = std::pow(x - origin_x,2)+std::pow(y - origin_y,2);
			if (d<=std::pow(r,2)){
				set_point(x,y,val);
			}
		}
	}
}
// Save image
void image::save(std::string filename){
	std::ofstream out;
	out.open (filename, std::ios::out);
	out << "P1 " << width << " " << height << "\n" << this->pixels;
	out.close();
}