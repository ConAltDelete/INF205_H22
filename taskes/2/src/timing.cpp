#include <chrono>

std::chrono::time_point timestamp_function(*funcptr, int argv[]){
	/*
	 * times a function "funcptr" with the arguments "argv" and return the duration.
	 * */
	auto t0 = std::chrono::high_resolution_clock::now();
	funcptr(argv);
	auto t1 = std::chrono::high_resolution_clock::now();
	auto delta_t = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
	return delta_t;
}

std::chrono::time_point worst_case(*funcptr, int argv[]){
	/*
	 * estimates the worst case senario
	 * */
}

std::chrono::time_point avg_case(*funcptr, int argv[]){
	/*
	 * estimates the avg case senario
	 * */
}

std::chrono::time_point best_case(*funcptr, int argv[]){
	/*
	 * estimate the best case senario
	 * */
}
