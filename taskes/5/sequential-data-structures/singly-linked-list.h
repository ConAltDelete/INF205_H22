#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <cassert>
#include "sequence.h"

namespace seq
{
   class SinglyLinkedListNode
   {
   public:
      // return a reference to the stored item
      int& get_item() { return this->item; }

      // return pointer to next node, or nullptr if this is the final node
      SinglyLinkedListNode* get_next() const { return this->next; }

      // overwrite the item stored in this node
      void set_item(int in_item) { this->item = in_item; }

   private:
      int item = 0;
      SinglyLinkedListNode* next = nullptr;

      // attach a node to this node
      // if there was a node attached to this previously, it is NOT deleted!
      void set_next(SinglyLinkedListNode* in_next) { this->next = in_next; }
      
      friend class SinglyLinkedList;  // allow SinglyLinkedList to access private members
   };

   class SinglyLinkedList: public Sequence
   {
   public:
      bool empty() const { return (this->head == nullptr); }  // test whether the singly linked list is empty
      size_t size() const;  // return the size (number of items in the singly linked list)

      // it is the caller's responsibility to ensure that the list is not empty when calling front() or back()!
      int& front() { assert(this->head); return this->head->get_item(); }  // return a reference to the first item
      int& back()  { assert(this->tail); return this->tail->get_item(); }  // return a reference to the final item

      // return a reference to the item at position i of the list, counting from 0
      // it is the caller's responsibility that the index is within range
      int& at(int i) { return this->index(i)->get_item(); }
      
      // return pointer to the head/tail node
      SinglyLinkedListNode* begin() const { return this->head; }
      SinglyLinkedListNode* end() const { return this->tail; }
      
      // return pointer to the node at position i, counting from 0
      SinglyLinkedListNode* index(int i) const;

      /*
       * accepts an additional item into the singly linked list;
       * by default, this is done at the back end of the list
       * call push_front(...) to push an element at the front
       * 
       * the list takes ownership of the copy (but not of the original!)
       */
      void push(const int& pushed_item) { this->push_back(pushed_item); }
      void push_back(const int& pushed_item);
      void push_front(const int& pushed_item);

      /*
       * removes an item from the list (front end by default)
       * to do the same at the back, call pop_back()
       */
      void pop() { this->pop_front(); }
      void pop_front();
      void pop_back();
      void clear() { while(!this->empty()) this->pop(); }  // remove all the items from the list

      // it is the caller's responsibility that the index is within range
      void insert_at(int i, const int& inserted_item);  // insert an item at index i
      void erase_at(int i);  // remove the item at index i
      
      // it is the caller's responsibility that the node is actually part of the list
      void insert_successor_to(SinglyLinkedListNode* predecessor, const int& inserted_item);  // insert an item after given node
      void erase_successor_to(SinglyLinkedListNode* predecessor);  // remove the item after given node
      
      ~SinglyLinkedList() { this->clear(); }

   private:
      SinglyLinkedListNode* head = nullptr;
      SinglyLinkedListNode* tail = nullptr;
   };
}

#endif
