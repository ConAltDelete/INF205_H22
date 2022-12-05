#include"coordstruct.h"

coords get_next_dir(coords A, coords B) {
	/*
	 *	Gets the unit direction A -> B
	 * */

	coords diff = B - A;

	int x,y;

	x = diff.x + diff.y;
	y = -diff.x + diff.y;


	if(x != 0){
		x /= std::abs(x);
	}
	if(y != 0){
		y /= std::abs(y);
	}

	return coords{x,y};
}

std::vector<coords> contour(std::vector<coords> image, coords start_point /*start point is a non-zero piyel*/, coords pre_point){
	/*
	 * Finds the contour of a shape.
	 * */
	coords term_point = start_point; // start, and end
	coords current = start_point;

	coords dir, attempt, pre, first_dir; // unit direction (1,0),(1,1),(-1,0),(0,1), etc
	
	pre = pre_point;

	std::vector<coords> ret;
	bool found_point = false;
	std::cout << "Starting contour...\n";

	do{
		first_dir = pre - current;
		dir = get_next_dir(current,pre);
		while(!found_point){
			attempt = coords{current.x + dir.x, current.y + dir.y};
			if(std::find(image.begin(), image.end(), attempt) != image.end()){
				found_point = true;
				ret.push_back(current);
				pre = current;
				current = attempt;
				std::cout << "found point\n";
			} else {
				dir = get_next_dir(current, attempt);
			}
		}
		found_point = false;
	}while(!(term_point == current));
	if(ret.size() < 10){
		std::cout << "weird contour: \n\t";
		std::cout << " dir: x = " << dir.x << " y = " << dir.y;
		std::cout << " cord: x = " << attempt.x << " y = " << attempt.y;
		std::cout << " curr: x = " << current.x << " y = " << current.y << "\n";
	}
	std::cout << "Done with contour.\n";

	return ret;
}
