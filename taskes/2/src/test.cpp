#include "PNG.cpp"


int main(int argc, const char* argv[])
{
    std::vector<int> primes(100);
    size_t count = prime_sieve(primes.begin(), primes.end());
    // display the primes
    for (size_t i = 0; i < count; ++i)
     	std::cout << primes[i] << " ";
     	std::cout << std::endl;
    return 1;
}
