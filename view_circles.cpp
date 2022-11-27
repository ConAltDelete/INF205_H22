
#include <iostream>
#include <fstream>


int x, y, r;
//Just for testing purpouses
x = 5;
y = 3;
r = 70;

// standard text for all circles
string ps_circle;
ps_circle = "0 360 arc fill";

// making a file for the PostScript code
ofstream fcircle("circles.txt");

for (int i = 0; i < 5; i++) {
    ++x, ++y, ++r;
    fcircle <<x<<" "<<y<<" "<<r<<" "<<ps_circle<<"\n";
}

fcircle.close();

// Just for confirmation atm
cout<<x<<" "<<y<<" "<<r<<" "<<ps_circle <<endl;
