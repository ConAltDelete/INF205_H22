#include <iostream>
#include <cmath>

const float pos = (1+std::sqrt(5))/2;
const float neg = (1-std::sqrt(5))/2;

bool check_if_fib(int x) {
	int estimate_n = std::log(x)/std::log(pos);
	
	int fib_n = (std::pow(pos,estimate_n)-std::pow(neg,estimate_n))/std::sqrt(5);
	int fib_p = (std::pow(pos,estimate_n-1)-std::pow(neg,estimate_n-1))/std::sqrt(5);
	
	int fibo_next;

	while( x >= fib_n){
		std::cout << 
			estimate_n
			<< "\t"
			<< fib_n
			<< "\n";

		fibo_next = fib_n + fib_p;

		estimate_n++;

		fib_p = fib_n;
		fib_n = fibo_next;
	}
	return x == fib_p;
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

int main() {
	int y = 876545678;

	//if(print_fibo_until(y)){
	if(check_if_fib(y)){
		std::cout << y << " is a Fibonacci number\n";
	} else {
		std::cout << y << " is not a Fibonacci number\n";
	}

	return 0;
}
