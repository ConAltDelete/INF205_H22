#include<iostream>
#include<vector>
#include<algorithm>

struct coords {
	int x;
	int y;

	bool operator==(coords const &a){
		return (this->x == a.x)&&(this->y == a.y);
	}
};

int main() {
	std::vector<coords> window = {
		coords{-1,1},
		coords{0,0},
		coords{1,1}
	};

	std::cout << (std::find(window.begin(),window.end(),coords{0,0}) != window.end()) << "\n";
	std::cout << (std::find(window.begin(),window.end(),coords{0,1}) != window.end()) << "\n";
	std::cout << (std::find(window.begin(),window.end(),coords{1,1}) != window.end()) << "\n";
	return 0;
}
