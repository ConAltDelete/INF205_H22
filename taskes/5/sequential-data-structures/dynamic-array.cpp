#include <algorithm>
#include <cassert>

#include "dynamic-array.h"

using namespace seq;

// remove all the items from the array
void DynamicArray::clear()
{
   if(this->values) delete this->values;
   this->values = nullptr;
   this->logical_size = 0;
   this->capacity = 0;
}

// insert an item at index i
void DynamicArray::insert_at(int i, const int& inserted_item)
{
   assert((i >= 0) && (this->logical_size >= i));
   
   // catch the case where capacity is exhausted and we need to allocate more memory
   if(this->logical_size == this->capacity)
   {
      size_t new_capacity = 2 * this->capacity;
      if(new_capacity == 0) new_capacity = 1;
      this->resize(new_capacity);
   }
   assert(this->capacity > this->logical_size);
   
   // shift all elements from index i onward one to the right
   // we use a temporary storage and copy() from <algorithm> to do this efficiently
   size_t shifted_elements = this->logical_size - i;
   if(shifted_elements > 0)
   {
      int* temp_storage = new int[shifted_elements]();
      
      // copy values[i] to values[i+shifted_elements-1] into temp_storage
      std::copy(this->values + i, this->values + i + shifted_elements, temp_storage);
      
      // copy all of temp_storage into values[i+1] to values[logical_size]
      std::copy(temp_storage, temp_storage + shifted_elements, &this->values[i+1]);
      delete temp_storage;
   }
   
   // now we can write the inserted item into values[i]
   this->logical_size++;
   this->values[i] = inserted_item;
}

// remove the item at index i
void DynamicArray::erase_at(int i)
{
   assert((i >= 0) && this->logical_size > i);
   
   // shift all elements from index i+1 onward one to the left
   // we use a temporary storage and copy() from <algorithm> to do this efficiently
   size_t shifted_elements = this->logical_size - i - 1;
   if(shifted_elements > 0)
   {
      int* temp_storage = new int[shifted_elements]();
      
      // copy values[i+1] to values[logical_size-1] into temp_storage
      std::copy(this->values + i+1, this->values + this->logical_size, temp_storage);
      
      // copy all of temp_storage into values[i] to values[logical_size-2]
      std::copy(temp_storage, temp_storage + shifted_elements, &this->values[i]);
      delete temp_storage;
   }
   this->logical_size--;  // with this, we are done with the task
   
   // now let us see whether we have deleted so many items that we should resize to save memory
   if(this->capacity/2 >= this->logical_size) this->resize(this->capacity/2);
}

// allocate static array with "new_capacity" elements,
// copy the contents there, and delete the previous static array
void DynamicArray::resize(size_t new_capacity)
{
   assert(new_capacity > this->logical_size);
   int* allocated_memory = new int[new_capacity]();
   
   if(this->values != nullptr)
   {
      // use <algorithm> library construct for efficient memory-level copying
      // take values[0] to values[logical-size-1] and copy it into allocated_memory
      std::copy(this->values, this->values + this->logical_size, allocated_memory);

      delete this->values; // now we can delete the old storage
   }

   // update class properties
   this->values = allocated_memory;
   this->capacity = new_capacity;
}
