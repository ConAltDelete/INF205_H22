//#include "PNG.h"
#include <iostream>
#include<algorithm>
#include<vector>
// requires Iterator satisfies RandomAccessIterator
template <typename Iterator>
size_t prime_sieve(Iterator start, Iterator end)
	/*
	 * Creates an iterator with prime numbers using the "Sive of Eratosthenes"
	 *
	 * sample code:
	 * int main(int argc, const char* argv[])
     * {
     * std::vector<int> primes(100);
     * size_t count = prime_sieve(primes.begin(), primes.end());
     * // display the primes
     * for (size_t i = 0; i < count; ++i)
     *   std::cout << primes[i] << " ";
     *   std::cout << std::endl;
     *   return 1;
	 * }
	 *
	 * source (date[ISO]: 2022/09/15) : https://rosettacode.org/wiki/Sieve_of_Eratosthenes#C++
	 * */
{
    if (start == end) return 0;
    // clear the container with 0
    std::fill(start, end, 0);
    // mark composites with 1
    for (Iterator prime_it = start + 1; prime_it != end; ++prime_it)
    {
        if (*prime_it == 1) continue;
        // determine the prime number represented by this iterator location
        size_t stride = (prime_it - start) + 1;
        // mark all multiples of this prime number up to max
        Iterator mark_it = prime_it;
        while ((end - mark_it) > stride)
        {
            std::advance(mark_it, stride);
            *mark_it = 1;
        }
    }
    // copy marked primes into container
    Iterator out_it = start;
    for (Iterator it = start + 1; it != end; ++it)
    {
        if (*it == 0)
        {
            *out_it = (it - start) + 1;
            ++out_it;
        }
    }
    return out_it - start;
}
