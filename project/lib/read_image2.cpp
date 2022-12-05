#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "coordstruct.h"

std::vector<coords> read_file ( std::string filename, int &h,int &w )
	/*
	 * Reads an pbm file and converts it to a vector of coordiantes.
	 * */
{
    int width, height;
    std::ifstream in;
    std::vector<std::string> file_parts;
    std::string line;
    std::string all_points;

    // Read each line in the file
    in.open ( filename, std::ios::in );
    while ( std::getline(in,line) )
    {
        // Split each line by spaces
        std::vector<std::string> line_parts;
        std::stringstream linestream(line);
        std::string token;
        while ( std::getline ( linestream, token, ' ' ) )
            line_parts.push_back(token);

        // Keep the tokens unless the line is a comment
        if ( line_parts[0][0] != '#' )
            for ( std::string s : line_parts )
                file_parts.push_back(s);
    }
    in.close();

    // Validate that what we just read makes sense:
    if ( file_parts[0].compare("P1") == 0 ) // Check that this is a PBM file
    {
        width  = std::stoi(file_parts[1]);  // Read the image size
        height = std::stoi(file_parts[2]);

        // Concatenate all the '0's and '1's into one string
        for ( int i=3; i<file_parts.size(); i++ )
            all_points += file_parts[i];

        // Warn if something went wrong with the parsing
        if ( all_points.length() != width*height )
            std::cerr << "Could not read '" << filename << "', mismatched size "
                      << width << "x" << height << " and image data length."
                      << std::endl;
    }

    // Generate coord pairs for all the points where pixel value is '1'
    h = height; w = width;
    std::vector<coords> result;
    for ( int y=0; y<height; y++ )
        for ( int x=0; x<width; x++ )
            if ( all_points[y*width+x] == '1' )
                result.push_back(coords{x,y});

    // Deliver result and close shop
    return result;
}
