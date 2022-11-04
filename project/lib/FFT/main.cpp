#include "FFT.h"

int main() {
	FFT::test_FFT().print_int(5);

	FFT::test_FFT().print_int(FFT::test_FFT().sum(1,9));
	return 0;
}
