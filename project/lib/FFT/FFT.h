#ifndef LIB_FFT
#define LIB_FFT
#include<complex>

#define PI 2*std::acos(0.0)

namespace FFT {
	class test_FFT {
		public:
			void print_int(int i);
			int sum(int a, int b);
	};
	class DFFT {
		std::complex* transform(std::complex[] coords,const size_t array_length, int degree_n);
		std::complex* inverse(std::complex[],const size_t array_length);
	};
}
#endif
