#ifndef LIB_FFT
#define LIB_FFT

#include<iostream>
#include <bits/stdc++.h>
#include<complex>

#define PI 2*std::acos(0.0)

namespace FFT {
	class test_FFT {
		public:
			void print_int(int i);
			int sum(int a, int b);
	};
	class DFFT {
		public:
			std::complex<float>* DFT(std::complex<float> coords[],const size_t array_length, int degree_n);
			std::complex<float>* transform(std::complex<float> coords[],const size_t array_length, int degree_n);
			std::complex<float>* inverse(std::complex<float> coeff[],const size_t array_length);
			std::complex<float>* prim_root(int n, int radical);
	};
}
#endif
