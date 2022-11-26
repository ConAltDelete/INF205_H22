
#include <iostream>
/*
int ps_x, ps_y, ps_r;
int x = 5;
int y = 3;
int r = 70;


for (int obj:obj_list){
    ps_x = x
    ps_y = y
    ps_r = r

}

// Translation to PostScript
FILE *outfile;
outfile = fopen("myfile.ps", "w");

fprintf(outfile,
    "%%!\n"
    "%d %d moveto\n"
    "%d %d lineto\n"
    "%d %d lineto\n"
    "%d %d lineto\n"
    "%d %d lineto\n"
    "stroke\n"
    "showpage\n",
    0, 0,
    120, 120,
    144, 120,
    200, 122,
    0, 0
);
*/

string x, y, r;
x = "5 ";
y = "3 ";
r = "70 ";
string ps_circle;
ps_circle = x+y+r+"0 360 arc fill";

cout<< ps_circle <<endl;
