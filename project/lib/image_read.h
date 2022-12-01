#ifndef IMAGE_READ
#define IMAGE_READ

#include "coordstruct.h"
#include <fstream>
#include <string>
#include <vector>

/*
 * reads the image and returns a vector with coords for non-zero pixel values.
 */
std::vector<coords> read_image(std::string image_path);

#endif
