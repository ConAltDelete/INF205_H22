#include "singly-linked-list.h"

using namespace seq;

// return the size (number of items in the singly linked list)
size_t SinglyLinkedList::size() const
{
   size_t count = 0;
   for(SinglyLinkedListNode* n = this->head; n != nullptr; n = n->get_next()) count++;
   return count;
}

// return pointer to the node at position i, counting from 0
SinglyLinkedListNode* SinglyLinkedList::index(int i) const
{
   SinglyLinkedListNode* n = this->head;
   for(int k = 0; k < i; k++)
   {
      assert(n != nullptr);
      n = n->get_next();
   }
   return n;
}

// add an item at the end of the list
void SinglyLinkedList::push_back(const int& pushed_item)
{
   SinglyLinkedListNode* new_node = new SinglyLinkedListNode;
   new_node->set_item(pushed_item);
   
   if(this->empty()) this->head = new_node;
   else this->tail->set_next(new_node);
   this->tail = new_node;
}

// add an item at the beginning of the list
void SinglyLinkedList::push_front(const int& pushed_item)
{
   SinglyLinkedListNode* new_node = new SinglyLinkedListNode;
   new_node->set_item(pushed_item);
   
   if(this->empty()) this->tail = new_node;
   else new_node->set_next(this->head->get_next());
   this->head = new_node;
}

// remove the head node and item
void SinglyLinkedList::pop_front()
{
   if(this->empty()) return;  // nothing there to remove
   SinglyLinkedListNode* successor = this->head->get_next();
   
   delete this->head;
   this->head = successor;  // successor of the previous head is the new head
   if(this->head == nullptr) this->tail = nullptr;  // catch special case: the list is now empty
}

// remove the tail node and item
// note: in a singly linked list, we need to walk step by step to the end!
void SinglyLinkedList::pop_back()
{
   if(this->empty()) return;  // nothing there to remove
   
   // list only contains one element
   if(this->head->get_next() == nullptr)
   {
      delete this->head;
      this->head = nullptr;
      this->tail = nullptr;
      return;
   }
   
   /*
    * walk through until "third" is nullptr, second is the last element, and first is the second-to-last
    */
   SinglyLinkedListNode* first = this->head;
   SinglyLinkedListNode* second = first->get_next();
   SinglyLinkedListNode* third = second->get_next();
   while(third != nullptr)
   {
      first = second;
      second = third;
      third = third->get_next();
   }
   
   /*
    * remove "second"
    */
   if(this->tail == second) this->tail = first;
   first->set_next(nullptr);
   delete second;
}

// insert an item at index i
void SinglyLinkedList::insert_at(int i, const int& inserted_item)
{
   if(i == 0)
   {
      this->push_front(inserted_item);
      return;
   }
   SinglyLinkedListNode* predecessor = this->index(i-1);
   this->insert_successor_to(predecessor, inserted_item);
}

// remove the item at index i
void SinglyLinkedList::erase_at(int i)
{
   if(i == 0)
   {
      this->pop_front();
      return;
   }
   SinglyLinkedListNode* predecessor = this->index(i-1);
   this->erase_successor_to(predecessor);
}

// insert an item after given node
void SinglyLinkedList::insert_successor_to(SinglyLinkedListNode* predecessor, const int& inserted_item)
{
   SinglyLinkedListNode* new_node =  new SinglyLinkedListNode;
   new_node->set_item(inserted_item);
   
   SinglyLinkedListNode* successor = predecessor->get_next();
   predecessor->set_next(new_node);
   new_node->set_next(successor);
   
   if(!successor) this->tail = new_node;
}

// remove the item after given node
void SinglyLinkedList::erase_successor_to(SinglyLinkedListNode* predecessor)
{
   SinglyLinkedListNode* erased_node = predecessor->get_next();
   SinglyLinkedListNode* new_successor = erased_node->get_next();
   
   predecessor->set_next(new_successor);
   if(new_successor == nullptr) this->tail = predecessor;
   delete erased_node;
}
