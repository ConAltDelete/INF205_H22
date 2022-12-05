#include "coordstruct.h"
#include "read_image2.cpp"
#include "contour.cpp"
#include "ARCDIC.cpp"
#include "view_circles.cpp"
#include <tuple>

coords max_right(std::vector<coords> cont, coords point){
	/*
	 * Finds the point that is the oposit to current point.
	 * */
	coords max_point = coords{0,0};
	for(auto p : cont){
		if(p.x >= max_point.x && p.y == point.y){
			max_point = p;
		}
	}
	return max_point;
}

coords coords_mod(coords p,int max_h,int max_w){
	/*
	 * Constrains a point p to a box with width max_w, and hight max_h.
	 * */
	coords new_p = p;
	if(new_p.x >= max_w){
		//std::cout << "Wall hit at x =" << new_p.x << "! y = " << new_p.y <<"\n";
		new_p.x = 0;
		new_p.y++;
	}
	if(new_p.y >= max_h){
		//std::cout << "floor hit at y = " << new_p.y << "! x= " << new_p.x << "\n";
		new_p.y = 0;
	}
	return new_p;
}

int main(){
	int length, hight;

	std::vector<coords> image_binary = read_file("image.pbm",hight,length);			// read_image2.cpp
	coords pre = coords{-1,0}, curr = coords{0,0};
	std::vector<coords> img_contour;
	std::vector<std::tuple<int,std::vector<coords>>> blobs;
	std::vector<Circle> circles,found;
	
	int pre_label = -1,label = 0;

	std::cout << "read image, size: " << image_binary.size() << "\n"; 

	while(!(curr == coords{length-1,hight-1})){
		if(label != pre_label){
			std::cout << "current label: " << label << "\n";
			pre_label = label;
		}
		for(auto  p: blobs){
			if(std::find(std::get<1>(p).begin(),std::get<1>(p).end(),curr) != std::get<1>(p).end()){
				curr = max_right(std::get<1>(p),curr);
				curr = coords_mod(curr + coords{2,0}, hight,length);
				pre = curr - coords{1,0};
				continue;
			}
		}
		if(std::find(image_binary.begin(),image_binary.end(),curr) != image_binary.end()){
			img_contour = contour(image_binary,curr,pre);
			curr = max_right(img_contour,curr);
			curr = coords_mod(curr + coords{2,0}, hight,length);
			pre = curr - coords{1,0};
			blobs.push_back(std::tuple<int,std::vector<coords>>{label,img_contour});
			label++;
		}
		curr = coords_mod(curr + coords{1,0}, hight,length);
		pre = curr - coords{1,0};
	}

	std::cout << "Found all blobs!\n";

	for(auto b : blobs){
		std::cout << "current label: " << std::get<0>(b) << "\n";
		found = find_circles(std::get<1>(b),0.2);// ARCDIC.cpp
		circles.insert(circles.end(),found.begin(),found.end());
	}
	draw_circle(circles);								// view_circles.cpp

}
