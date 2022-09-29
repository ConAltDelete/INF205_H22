#include <chrono>
#include <vector>
#include "PNG.h"
#include "timing.h"

long long timestamp_function(funcptr func, int argv){
	/*
	 * times a function "funcptr" with the arguments "argv" and return the duration.
	 * */
	auto t0 = std::chrono::high_resolution_clock::now();
	func(argv);
	auto t1 = std::chrono::high_resolution_clock::now();
	auto delta_t = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
	return delta_t;
}

long long worst_case(funcptr func, int n){
	/*
	 * estimates the worst case senario
	 * */
	std::vector<int> primes{n};

	prime_sieve(primes.begin(), primes.end());
	long long avg_time = 0;
	int i = 0;

	for(auto p : primes){
		avg_time += (timestamp_function(func, p) - avg_time)/(i+1);
		i++;
	}

	return avg_time;
}

long long avg_case(funcptr func, int n){
	/*
	 * estimates the avg case senario
	 * */
	long long avg_time = 0;

	for(int k = 0; k < n; k++){
		avg_time += (timestamp_function(func, k+1) - avg_time)/(k+1);
	}

	return avg_time;
}

long long best_case(funcptr func, int n){
	/*
	 * estimate the best case senario
	 * */
	long long avg_time = 0;

	for(int k = 0; k < n; k++){
		avg_time += (timestamp_function(func, 2*k) - avg_time)/(k+1);
	}

	return avg_time;
}
