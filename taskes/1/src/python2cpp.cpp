#include <iostream>
#include <cmath>
#include <string>

const float pos = (1+std::sqrt(5))/2;
const float neg = (1-std::sqrt(5))/2;
const float underside = std::sqrt(5);

bool check_if_fib(int x) {
	/*
	 * performing a test using Binet's idetification formula
	 */
	long long test1 = 5*std::pow(x,2)+4;
	long long test2 = 5*std::pow(x,2)-4;
	
	bool ver1 = std::ceil(std::sqrt(test1))*std::floor(std::sqrt(test1)) == test1;
	bool ver2 = std::ceil(std::sqrt(test2))*std::floor(std::sqrt(test2)) == test2;

	return (ver1 || ver2);
}

bool print_fibo_until(int x) {
	int n, fibo_n = 1;
	int fibo_previous = 0;

	int fibo_next;

	while( x >= fibo_n){
		std::cout << n << "\t" << fibo_n << std::endl;

		fibo_next = fibo_n + fibo_previous;

		n++;

		fibo_previous = fibo_n;
		fibo_n = fibo_next;
	}
	return x == fibo_previous;
}

int main(int argn, char** argv) {
	int y;
	if(argn > 1){
		y = std::stoi(argv[1],nullptr,10);
	} else {
		y = 17711;
	}

	std::cout << y << " is " << (check_if_fib(y)?"":"not ") << "a Fibonacci number\n";

	return 0;
}
