#include <iostream>
#include <fstream>
#include <Magick++.h>
/// Dette er en kladd
//  Her vil du finnne alle mine forskjellige fors�k


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
    fcircle <<x<<' '<<y<<' '<<r<<' '<<ps_circle<<"\n";
}

fcircle.close();

// Just for confirmation atm
cout<<x<<" "<<y<<" "<<r<<" "<<ps_circle <<endl;


///__________________

// Fikk feilkode p� denne koden:
// Compiling file using gcc  -o a.out "circles.txt"
// Running file '.' is not recognized as an internal or external command,
// operable program or batch file.

// A C++ program that compiles and runs another C++
// program

char filename[100];
cout << "Enter file name to compile ";
cin.getline(filename, 100);

// Build command to execute.  For example if the input
// file name is a.cpp, then str holds "gcc -o a.out a.cpp"
// Here -o is used to specify executable file name
string str = "gcc ";
str = str + " -o a.out " + filename;

// Convert string to const char * as system requires
// parameter of type const char *
const char *command = str.c_str();

cout << "Compiling file using " << command << endl;
system(command);

cout << "\nRunning file ";
    system("./a.out");


///__________________

// Fikk ikke til � kj�re(?) biblioteket. Jeg har f�tt til � vise figuren til IM,
// som skal v�re testen p� om IM er installert korrekt, men codeblocks finner ikke biblioteket.
// ImageMagick sin sirkeltegner. Link f�lger:
// https://imagemagick.org/Usage/draw/#primitives


// For � p�kalle ImageMagick for windows. Ga ikke resultat for meg.
int main(int argc,char **argv){
    InitializeMagick(*argv);

    // Har ikke f�tt testet denne sirkeltegneren. Det er flere � velge mellom.
    // F�lg tidligere gitt link
    magick -size 100x60 xc:skyblue -fill white -stroke black \
              -draw "circle 50,30 40,10"     draw_circle.gif
    return 0
}
