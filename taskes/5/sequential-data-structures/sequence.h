#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>

namespace seq
{
   class Sequence
   {
   public:
      virtual bool empty() const = 0;   // test whether the sequence is empty
      virtual size_t size() const = 0;  // return the size (number of items in the sequence)
      
      // it is the caller's responsibility to ensure that the sequence is not empty when calling front() or back()!
      virtual int& front() = 0;  // return a reference to the first item
      virtual int& back() = 0;   // return a reference to the final item
      
      // return a reference to the item at position i of the sequence, counting from 0
      // it is the caller's responsibility that the index is within range
      virtual int& at(int i) = 0;

      /*
       * accepts an additional item into the sequence (front or back);
       * the pushed item is passed by reference, but a copy of it is stored in the Sequence
       * the Sequence takes ownership of the copy (but not of the original!)
       */
      virtual void push(const int& pushed_item) = 0;  // default push operation (front or back)
      virtual void push_front(const int& pushed_item) = 0;
      virtual void push_back(const int& pushed_item) = 0;

      virtual void pop() = 0;  // default pop operation (front or back)
      virtual void pop_front() = 0;  // remove the first element
      virtual void pop_back() = 0;   // remove the last element
      virtual void clear() = 0;  // remove all the items from the sequence

      // it is the caller's responsibility that the index is within range
      virtual void insert_at(int i, const int& inserted_item) = 0;  // insert an item at index i
      virtual void erase_at(int i) = 0;  // remove the item at index i
   };
}

#endif
