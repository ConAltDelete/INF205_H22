#include "FFT.h"
#include<iostream>
#include <bits/stdc++.h>


int main() {
	std::complex<float> samples[] = {
		std::complex<float>{4,5},
		std::complex<float>{ 0.79097172,0.678704},
		std::complex<float>{0.41032989,0.77437286},
		std::complex<float>{-0.2395095,-0.22158645},
		std::complex<float>{-1.96179212,0.7685096}
	};

	FFT::DFFT sup = FFT::DFFT();

	std::complex<float>* coff = sup.DFT(samples,5,3);

	for(int i = 0;i < 7;i++){
		std::cout << "coeff: " <<  coff[i] << "\n";
	}

	delete coff;

	return 0;
}


std::complex<float>* FFT::DFFT::DFT(std::complex<float> coords[], const size_t array_length, int degree_n){
	const int K = std::min((size_t)degree_n, array_length); // We can't have a degree higher than the resolusion of the signal. It's only possible in the continius case.

	std::complex<float>* w = FFT::DFFT::prim_root(array_length,array_length);
	
	static std::complex<float>* F_coeff = (std::complex<float>*)malloc((2*K+1)*sizeof(std::complex<float>)); // calculates the negative and positiv rotations.

	std::complex<float> temp_sum; 
	std::complex<float> trans_coeff; // teporary coeffisisent that "removes" noice and generates the correct F_coeff

	std::cout << "K verdier: " << -K << "," << K + 1 <<"," << PI <<  "\n";

	for(int i = -K; i < K + 1; i++){
		temp_sum = std::complex<float>(0,0);
		trans_coeff = std::pow(w[i+K],-i);
		std::cout << "trans_coeff: " << trans_coeff << "\n";
		for(int t = 0; t < array_length; t++){
			temp_sum += coords[t]*std::pow(trans_coeff,t);
		}
		std::cout << "temp_sum: " << temp_sum << "\n";
		F_coeff[i+K] = temp_sum;
	}

	return F_coeff;
}

std::complex<float>* FFT::DFFT::prim_root(const int n, int radical){
	/*
	 *	Coputes the roots of unity
	 * */
	static std::complex<float>* roots = (std::complex<float>*)malloc(n*sizeof(std::complex<float>)); // 'static' is to make it possible to return the array.

	const float omega_const = 2*PI / radical;

	for(int k = 0; k < n; k++){
		roots[k] = std::complex<float>(std::cos(omega_const * k),std::sin(omega_const * k));
		std::cout << "root: " << roots[k] << "\n";
	}
	return roots;
}
