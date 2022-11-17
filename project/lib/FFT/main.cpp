#include "FFT.h"
#include<iostream>


int main() {
	std::complex<float> samples[] = {
		std::complex<float>{4,2},
		std::complex<float>{8,1},
		std::complex<float>{4,0},
		std::complex<float>{1,0},
		std::complex<float>{3,8}
	};

	std::complex<float>* coff = FFT::DFFT::DFT(samples,5,3);

	for(int i = 0;i < 5;i++){
		std::cout << coff[i] << "\n"; 
	}

	return 0;
}


std::complex<float>* FFT::DFFT::DFT(std::complex<float> coords[], const size_t array_length, int degree_n){
	int K = std::min(degree_n, array_length); // We can't have a degree higher than the resolusion of the signal. It's only possible in the continius case.

	std::complex<float>* w = FFT::prim_root(K,array_length);
	
	static std::complex<float> F_coeff[2*K+1]; // calculates the negative and positiv rotations.

	std::complex<float> temp_sum; 
	std::complex<float> trans_coeff; // teporary coeffisisent that "removes" noice and generates the correct F_coeff

	for(int i = -K/2; i < (int)K/2 - 1; i++){
		temp_sum = std::complex<float>(0,0);
		trans_coeff = std::pow(w[i+K/2],i);
		for(int t = 0; t < array_length; t++){
			temp_sum += coords[t]*trans_coeff;
		}
		F_coeff[i+K/2] = temp_sum;
	}

	return F_coeff;
}

std::complex<float>* FFT::DFFT::prim_root(int n, int radical){
	/*
	 *	Coputes the roots of unity
	 * */
	static std::complex<float> roots[n]; // 'static' is to make it possible to return the array.

	const float omega_const = 2*PI / radical;

	for(int k = 0; k < n; k++){
		roots[k] = std::complex<float>(std::cos(omega_const * k),std::sin(omega_const * k));
	}
	return roots;
}
