#include "coordstruct.h"
#include "read_image2.cpp"
#include "contour.cpp"
#include "ARCDIC.cpp"
#include "view_circles.cpp"
#include <tuple>

void intersection(std::vector<coords> &S1, std::vector<coords> &S2){
	for(auto c: S2){
		S2.erase(std::find(S2.begin(),S2.end(),c));
	}
}

int max_left(std::vector<coords> cont, coords point){
	
	int max_point = 0;
	for(int i = 0; i < cont.size(); i++){
		if(cont[i].x == point.x && cont[i].y > cont[max_point].y){
			max_point = i;
		}
	}
	return max_point;
}

coords coords_mod(coords p,int max_h,int max_w){
	coords new_p = p;
	if(p.x >= max_w){
		new_p.x = 0;
		new_p.y++;
	}
	if(p.y >= max_h){
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
	
	int label = 0;

	std::cout << "read image, size: " << image_binary.size() << "\n"; 

	while(!(curr == coords{length-1,hight-1})){
		std::cout << "Current label: " << label << "\n";
		for(auto  p: blobs){
			if(std::find(std::get<1>(p).begin(),std::get<1>(p).end(),curr) != std::get<1>(p).end()){
				curr = std::get<1>(p)[max_left(std::get<1>(p),curr)];
				curr = coords_mod(curr + coords{2,0}, hight,length);
				pre = curr - coords{1,0};
				continue;
			}
		}
		if(std::find(image_binary.begin(),image_binary.end(),curr) != image_binary.end()){
			img_contour = contour(image_binary,curr,pre);
			curr = img_contour[max_left(img_contour,curr)];
			curr = coords_mod(curr + coords{2,0}, hight,length);
			pre = curr - coords{1,0};
			blobs.push_back(std::tuple<int,std::vector<coords>>{label,img_contour});
			label++;
		}
		curr = coords_mod(curr + coords{1,0}, hight,length);
		pre = curr - coords{1,0};
		std::cout << "current point: {" << curr.x << ", " << curr.y << "\n";
	}

	std::cout << "Found all blobs!\n";

	for(auto b : blobs){
		std::cout << "current label: " << std::get<0>(b) << "\n";
		found = find_circles(std::get<1>(b),0.2);// ARCDIC.cpp
		circles.insert(circles.end(),found.begin(),found.end());
	}
	draw_circle(circles);								// view_circles.cpp

}
