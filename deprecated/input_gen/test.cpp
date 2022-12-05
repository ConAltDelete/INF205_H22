#include "read_image.cpp"

int main(){
	std::string file_name = "image.pbm";

	std::cout << "status: " << read_file(file_name) << "\n";
}
