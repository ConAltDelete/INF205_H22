#include"coordstruct.h"

coords get_next_dir(coords A, coords B) {
	/*
	 *	Gets the unit direction A -> B
	 * */

	coords diff = B - A;

	int x,y;

	x = diff.x + diff.y;
	y = -diff.x + diff.y;

	x = diff.x / std::abs(diff.x);
	y = diff.y / std::abs(diff.y);

	return coords{x,y};
}

std::vector<coords> contour(std::vector<coords> image, coords start_point /*start point is a non-zero piyel*/, coords pre_point){
	coords term_point = start_point; // start, and end
	coords current = start_point;

	coords dir, attempt, pre; // unit direction (1,0),(1,1),(-1,0),(0,1), etc
	
	pre = pre_point;

	std::vector<coords> ret;
	bool found_point = false;

	while(!(term_point == current)){
		dir = get_next_dir(current,pre);
		while(!found_point){
			attempt = coords{current.x + dir.x, current.y + dir.y};
			if(std::find(image.begin(), image.end(), attempt) != image.end()){
				found_point = true;
				ret.push_back(current);
				pre = current;
				current = attempt;
			} else {
				dir = get_next_dir(current, attempt);
			}
		}
		found_point = false;
	}

	return ret;
}
