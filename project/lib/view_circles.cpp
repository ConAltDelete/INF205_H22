#include "coordstruct.h"

void draw_circle(std::vector<Circle> obj_list){
	/*
	 * takes a vector of circles and insert them to a PostScript file.
	 * */
	// standard text for all circles
	// string ps_circle;
	// standard text for all circles
	// string ps_circle;
	std::string ps_circle = "0 360 arc fill";
	// making a file for the PostScript code
	std::ofstream fcircle("circles.ps");

	for(auto obj : obj_list) {
		fcircle << obj.colour << " setgray\n";
		fcircle << obj.x << ' ' << obj.y << ' ' << obj.R << ' ' << ps_circle << "\n";
	}
	fcircle << "showpage\n";
	fcircle.close();
}
