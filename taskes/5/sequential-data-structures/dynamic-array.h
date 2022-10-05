#include "sequence.h"

namespace seq
{
   class DynamicArray: public Sequence
   {
   public:
      bool empty() const { return (this->logical_size == 0); }   // test whether the array is empty
      size_t size() const { return this->logical_size; }  // return the logical size (number of items in the array)

      // it is the caller's responsibility to ensure that the array is not empty!
      int& front() { return this->values[0]; }  // return a reference to the first item
      int& back() { return this->values[this->logical_size - 1]; }   // return a reference to the final item

      // return a reference to the item at position i of the sequence, counting from 0
      // we use modulo arithmetics to avoid over-/underflow; will still fail for an empty array
      int& at(int i) { return this->values[i % this->logical_size]; }
      
      /*
       * accepts an additional item into the dynamic array;
       * by default, this is done at the back end of the array
       * call push_front(...) to push an element at the front
       * 
       * the array takes ownership of the copy (but not of the original!)
       */
      void push(const int& pushed_item) { this->push_back(pushed_item); }
      void push_back(const int& pushed_item) { this->insert_at(this->logical_size, pushed_item); }
      void push_front(const int& pushed_item) { this->insert_at(0, pushed_item); }

      /*
       * removes an item from the list (back end by default)
       * to do the same at the front, call pop_front()
       */
      void pop() { this->pop_back(); }
      void pop_front() { this->erase_at(0); }
      void pop_back() { this->erase_at(this->logical_size - 1); }
      void clear();  // remove all the items from the array
      
      void insert_at(int i, const int& inserted_item);  // insert an item at index i
      void erase_at(int i);  // remove the item at index i
      
      // overwrite the element at index i
      // we use modulo arithmetics to avoid over-/underflow; will still fail for an empty array
      void set_value_at(int i, const int& in_item) { this->values[i % this->logical_size] = in_item; }
      
      ~DynamicArray() { this->clear(); }

   private:
      // this is a static C/C++ array containing the actual data
      // it is owned by the dynamic array
      int* values = nullptr;
      
      size_t logical_size = 0;  // how many data items are we actually storing?
      size_t capacity = 0;  // how much memory did we allocate?
      
      void resize(size_t new_capacity);  // shift to static array with increased/decreased capacity
   };
}
