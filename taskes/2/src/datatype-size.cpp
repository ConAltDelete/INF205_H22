#include <iostream>
using namespace std;

int main()
{
   /*
    * int demo
    */
   int demo_int = -1;
   cout << "size of int:\t\t" << sizeof(demo_int) << "\t(int)-1\t\t\t= " << demo_int << "\n\n";

   /*
    * short demo
    */
   short demo_short = -1;
   cout << "size of short:\t\t" << sizeof(demo_short) << "\t(short)-1\t\t= " << demo_short << "\n";

   /*
    * long demo
    */
   long demo_long = -1;
   cout << "size of long:\t\t" << sizeof(demo_long) << "\t(long)-1\t\t= " << demo_long << "\n";

   /*
    * long long demo
    */
   long long demo_longlong = -1;
   cout << "size of long long:\t" << sizeof(demo_longlong) << "\t(long long)-1\t\t= " << demo_longlong << "\n\n";

   /*
    * unsigned short demo
    */
   unsigned short demo_unsigned_short = -1;
   cout << "size of unsigned short:\t" << sizeof(demo_unsigned_short) << "\t(unsigned short)-1\t= " << demo_unsigned_short << "\n";

   /*
    * unsigned long long demo
    */
   unsigned long long demo_unsigned_longlong = -1;
   cout << "size of uns. long long:\t" << sizeof(demo_unsigned_longlong) << "\t(unsigned long long)-1\t= " << demo_unsigned_longlong << "\n\n";

   /*
    * bool demo
    */
   bool demo_bool = -1;
   cout << "size of bool:\t\t" << sizeof(demo_bool) << "\t(bool)-1\t\t= " << demo_bool << "\n";

   /*
    * char demo
    */
   char demo_char = -1;
   cout << "size of char:\t\t" << sizeof(demo_char) << "\t(char)-1\t\t= " << demo_char << "\n";

   /*
    * wchar_t demo
    */
   wchar_t demo_wchar_t = -1;
   cout << "size of wchar_t:\t" << sizeof(demo_wchar_t) << "\t(wchar_t)-1\t\t= " << demo_int << "\n\n";

   /*
    * float demo
    */
   float demo_float = -1;
   cout << "size of float:\t\t" << sizeof(demo_float) << "\t(float)-1\t\t= " <<demo_float << "\n";

   /*
    * double demo
    */
   double demo_double = -1;
   cout << "size of double:\t\t" << sizeof(demo_double) << "\t(double)-1\t\t= "<< demo_double << "\n";

   /*
    * long double demo
    */
   long double demo_long_double = -1;
   cout << "size of long double:\t" << sizeof(demo_long_double) << "\t(long double)-1\t\t= " << demo_long_double << "\n";
}

