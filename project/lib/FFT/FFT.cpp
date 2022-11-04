#include<iostream>
#include<cmath>
#include"FFT.h"

using namespace FFT;

void test_FFT::print_int(int i) {
	std::cout << i << "\n";
}

int test_FFT::sum(int a, int b){
	return a + b;
}

std::complex* FFT::DFFT(std::complex[] coords, const size_t array_length, int degree_n){
	\*
		Descreat Fast Fourier Transform

		Takes an array of complex coordiantes and transform them into an array of coefisants that incodes the "signal".
	*\

	for(int s = 1; s < std::log2(array_length),s++){
		m = 2<<s;
		omega_m = std::exp(2*PI*std::complex(0,1) / m);
		for(int k = 0, k < array_length; k++)
	}
}
