#include <iostream>

struct My_poo {
	int a;
	float liquid;

	int scale_poo(int noodles){
		return noodles * this->a / (int)this->liquid;
	}
	int scale_poo(int noodles, My_poo* shit){
		return noodles * (int)shit->liquid / shit->a * this->a / (int)this->liquid;
	}
};

int main(int argn, char** argv){
	My_poo turd = My_poo{4,9};
	My_poo lol  = My_poo{2,2};
	// turd.a = 4;
	// turd.liquid = 9;

	std::cout << turd.scale_poo(10) << "\n";
	std::cout << lol.scale_poo(20,&turd) << "\n";
}
