
#include <iostream>
#include <fstream>


int x, y, r;


// standard text for all circles
string ps_circle;
ps_circle = "0 360 arc fill";

// making a file for the PostScript code
ofstream fcircle("circles.txt");

for (int obj : obj_lst) {
    fcircle <<obj.x<<" "<<obj.y<<" "<<obj.r<<" "<<ps_circle<<"\n";
}

fcircle.close();

