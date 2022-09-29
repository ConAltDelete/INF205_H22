#ifndef TIME_MESSURE
#define TIME_MESSURE

#include <chrono>
#include <vector>
#include "PNG.h"

typedef bool (*funcptr)(int64_t); //function pointer decleration

long long timestamp_function(funcptr func, int argv);

long long worst_case(funcptr func, int n);
long long avg_case(funcptr func, int n);
long long best_case(funcptr func, int n);

#endif
