#ifndef HEADER_GUARD
#define HEADER_GUARD

struct coords{
	int x;
	int y;

	// Little tool to check whether I exist
	bool operator==(coords const &a){
		return (this->x == a.x) && (this->y == a.y);
	}
}

#endif