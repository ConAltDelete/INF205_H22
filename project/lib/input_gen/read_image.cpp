#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "coordstruct.h"

int read_file(std::string file_path){
	
	std::ifstream file(file_path);

	std::string line;

	std::getline(file, line);

	std::cout << "Header data: " << line << "\n"; // reading sizes
	
	std::vector<int> image_size;

	char* delim = " ";
	char* ptr_tracker;

	strtok_r(line,delim,&ptr_tracker); // tolkenizing... needs to be checked.

	image_size.push_back(strtok_s(NULL,delim,&ptr_tracker));
	image_size.push_back(strtok_s(NULL,delim,&ptr_tracker));

	std::getline(file,line); // data is on one line.
	
	std::string data = line;
	std::vector<coords> trans_data; //translated data

	for(int j = 0; j < image_size[1]; j++){
		for(int i = 0; i < image_size[0]; i++){
			if(data[i+image_size[1]*j] == '1'){
				std::cout << "Found one!";
				trans_data.push_back(coords{i,j});
			}
		}
	}

	return trans_data;
}
