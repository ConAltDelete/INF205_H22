
#include <iostream>
#include <fstream>

using namespace std;

// standard text for all circles
// string ps_circle;
string ps_circle;
ps_circle = "0 360 arc fill";

// making a file for the PostScript code
ofstream fcircle("circles.txt");



for (int obj : obj_lst) {
    fcircle <<obj.x<<' '<<obj.y<<' '<<obj.R<<' '<<ps_circle<<"\n";
}

fcircle.close();

