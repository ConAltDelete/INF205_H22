#include <cassert>
#include <chrono>
#include <iostream>

#include "dynamic-array.h"
#include "singly-linked-list.h"
#include "doubly_linked_list.h"

namespace
{
   /*
    * run a simple test
    */
   void test_sequence(seq::Sequence* sqn, int n, int m, std::ostream* os)
   {
      assert((m > 0) && (n > m));
      if(os) *os << "Push even numbers from 0 to " << 2*(n-1) << ".\n";
      for(int i = 0; i < n; i++) sqn->push(2*i);
      
      if(os) *os << "Overwrite element at index " << m/2 << " with 0.\n";
      int& item = sqn->at(m/2);
      item = 0;
      
      if(os) *os << "\nSize of sequence: " << sqn->size() << ".\n";
      if(os) *os << "Detaching " << m/2 << " elements from front:";
      for(int i = 0; i < m/2; i++)
      {
         if(os) *os << " " << sqn->front();
         sqn->pop_front();
      }
      if(os) *os << ".\nDetaching " << m/2 << " elements from back:";
      for(int i = 0; i < m/2; i++)
      {
         if(os) *os << " " << sqn->back();
         sqn->pop_back();
      }
      if(os) *os << ".\nSize of sequence: " << sqn->size() << ".\n";
      
      if(os) *os << "\nElement at index " << (n-m)/3 << ": " << sqn->at((n-m)/3) << ".\n";
      if(os) *os << "Element at index " << 2*(n-m)/3 << ": " << sqn->at(2*(n-m)/3) << ".\n";
      
      if(os) *os << "\nInsert " << m << " at index " << 2*(n-m)/3 << ".\n";
      sqn->insert_at(2*(n-m)/3, m);
      if(os) *os << "Size of sequence: " << sqn->size() << ".\n";
      
      if(os) *os << "\nDelete element at index " << (n-m)/3 << ".\n";
      sqn->erase_at((n-m)/3);
      if(os) *os << "Size of sequence: " << sqn->size() << ".\n";
      if(os) *os << "Element at index " << 2*(n-m)/3 - 1 << ": " << sqn->at(2*(n-m)/3 - 1) << ".\n";
      
      if(os) *os << "\nClearing.\n";
      sqn->clear();
      if(os) *os << "Size of sequence: " << sqn->size() << ".\n";
   }
   
   /*
    * return time measurement in units of seconds
    */
   float test_with_time_measurement(seq::Sequence* sqn, int iterations)
   {
      int sequence_length = 1000001;
      int deletions = 10;
      test_sequence(sqn, sequence_length, deletions, &std::cout);

      int log_entries = 10;
      std::cout << "\nNow repeat the above " << iterations << " times:\n";
      auto t0 = std::chrono::high_resolution_clock::now();
      for(int i = 0; i < iterations; i++)
      {
         test_sequence(sqn, sequence_length, deletions, nullptr);
         if((i+1) % (iterations/log_entries) == 0)
         {
            std::cout << "\t" << i+1 << "\n";
            std::cout.flush();  // make sure that status output is shown without delay
         }
      }
      auto t1 = std::chrono::high_resolution_clock::now();
      return 1.0e-06 * std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
   }
}

int main()
{
   int iterations = 1000;
   /*
   std::cout << "*** test with dynamic array ***\n";
   seq::DynamicArray dyna;
   float dyna_time = test_with_time_measurement(&dyna, iterations);
   
   std::cout << "\n\n*** test with singly linked list ***\n";
   seq::SinglyLinkedList sll;
   float sll_time = test_with_time_measurement(&sll, iterations);
   */
   /*
    * once the doubly linked list is implemented,
    * you should be able to run the same test on it
    */
   std::cout << "\n\n*** test with doubly linked list ***\n";
   seq::DoublyLinkedList dll;
   float dll_time = test_with_time_measurement(&dll, iterations);
   
   //std::cout << "\n\nRuntime for dynamic array:\t" << dyna_time << " s\n";
   //std::cout << "Runtime for singly linked list:\t" << sll_time << " s\n";
   
   std::cout << "Runtime for doubly linked list:\t" << dll_time << " s\n";

}
