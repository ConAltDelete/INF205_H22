
std::complex<float>* FFT::DFFT::DFT(std::complex<float> coords[], const size_t array_length, int degree_n){
	// const int K = std::min((size_t)degree_n, array_length); // We can't have a degree higher than the resolusion of the signal. It's only possible in the continius case.

	std::complex<float>* w = FFT::DFFT::prim_root(array_length,array_length);
	
	static std::complex<float>* F_coeff = (std::complex<float>*)malloc((array_length)*sizeof(std::complex<float>)); // calculates the negative and positiv rotations.

	std::complex<float> temp_sum; 
	std::complex<float> trans_coeff; // teporary coeffisisent that "removes" noice and generates the correct F_coeff

	for(int i = 0; i < array_length; i++){
		temp_sum = std::complex<float>(0,0);
		trans_coeff = std::pow(w[i],-i);
		std::cout << "trans - > w,-i,pow: " << w[i] << " , " << i << " , " << trans_coeff << "\n"; 
		for(int t = 0; t < array_length; t++){
			temp_sum += coords[t]*std::pow(trans_coeff,t);
			std::cout << "temp_sum at t= " << t << " : " << temp_sum << std::endl;
		}
		std::cout << "temp_sum: " << temp_sum << "\n";
		F_coeff[i] = temp_sum;
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
