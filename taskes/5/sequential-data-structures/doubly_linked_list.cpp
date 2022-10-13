#include <iostream>
#include "sequence.h"
#include "doubly_linked_list.h"

using namespace seq;

void DoublyLinkedList::go_to(int i){
	if(this->List_index < i){
		DLLNode* at_node = this->current_node;
		while(this->List_index != i){
			at_node = at_node->nptr;
			this->List_index++;
		}
		this->current_node = at_node;
	} else if(this->List_index > i){
		DLLNode* at_node = this->current_node;
		while(this->List_index != i){
			at_node = at_node->pptr;
			this->List_index--;
		}
		this->current_node = at_node;
	}
}

bool DoublyLinkedList::empty() const {
	return this->List_size == 0;
}
size_t DoublyLinkedList::size() const {
	return this->List_size;
}
size_t DoublyLinkedList::get_List_index(){
	return this->List_index;
}

int& DoublyLinkedList::front() {
	return this->Front->value;
}
int& DoublyLinkedList::back(){
	return this->Back->value;
}

int& DoublyLinkedList::at(int i){
	if(this->List_index == i){
		return this->current_node->value;
	}

	this->go_to(i);
	return this->current_node->value;

}

void DoublyLinkedList::push(const int& pushed_item){
	this->push_front(pushed_item);
}
void DoublyLinkedList::push_front(const int& pushed_item){
	if(this->current_node == nullptr){
		DLLNode* current_node = new DLLNode();
		current_node->value = pushed_item;
		this->current_node = current_node;
		this->List_size++;
		this->Front = this->current_node;
		this->Back = this->current_node;
	} else {
		DLLNode* new_node = new DLLNode();
		new_node->value = pushed_item;
		new_node->pptr = this->Front;
		this->Front->nptr = new_node;
		this->Front = new_node;
		this->List_size++;
	}
}

void DoublyLinkedList::push_back(const int& pushed_item){
	if(this->current_node == nullptr){
		DLLNode* current_node = new DLLNode();
		current_node->value = pushed_item;
		this->current_node = current_node;
		this->List_size++;
		this->Front = this->current_node;
		this->Back = this->current_node;
	} else {
		DLLNode* new_node = new DLLNode();
		new_node->value = pushed_item;
		new_node->nptr = this->Back;
		this->Back->pptr = new_node;
		this->List_size++;
		this->Back = new_node;
		this->List_index++;
	}
}


void DoublyLinkedList::pop(){this->pop_front();}
void DoublyLinkedList::pop_front(){
	if(this->current_node == this->Front && this->current_node->pptr != nullptr){
		this->current_node = this->current_node->pptr;
		this->List_index--;
	}
	if(this->current_node == this->Front && this->current_node->pptr == nullptr){
		delete this->current_node;
		this->Front = nullptr;
		this->Back  = nullptr;
		this->List_size--;
	} else if(this->Front != nullptr){
		DLLNode* placeholder = this->Front->pptr;
		placeholder->nptr = nullptr;
		delete this->Front;
		this->Front = placeholder;
		this->List_size--;
	}
}
void DoublyLinkedList::pop_back(){
	if(this->current_node == this->Back && this->current_node->nptr != nullptr){
		this->current_node = this->current_node->nptr;
		this->List_index++;
	}
	if(this->current_node == this->Back && this->current_node->nptr == nullptr){
		delete this->current_node;
		this->Front = nullptr;
		this->Back  = nullptr;
		this->List_size--;
	} else if(this->Back != nullptr){
		DLLNode* placeholder = this->Back->nptr;
		placeholder->pptr = nullptr;
		delete this->Back;
		this->Back = placeholder;
		this->List_size--;
	}
}
void DoublyLinkedList::clear(){
	/*
	 * 1) set position to Front or Back
	 * 2) pop until size == 0
	 * 3) delete value at List_index 0
	 * 4) profit
	 * */

	this->current_node = this->Back;

	while(this->List_size > 0){
		this->pop(); // deletes every value
	}
}

void DoublyLinkedList::insert_at(int i, const int& inserted_item){
	this->go_to(i);
	DLLNode* new_node = new DLLNode();
	new_node->value = inserted_item;
	new_node->pptr = this->current_node->pptr;
	new_node->nptr = this->current_node;

	this->current_node->pptr->nptr = new_node;
	this->current_node->pptr = new_node;
	this->List_index++;
	this->List_size++;
}
void DoublyLinkedList::erase_at(int i){
	DLLNode* prob_node;
	
	this->go_to(i);

	prob_node = this->current_node;

	prob_node->pptr->nptr = prob_node->nptr;
	prob_node->nptr->pptr = prob_node->pptr;
	this->current_node = prob_node->pptr;
	delete prob_node;
	this->List_size--;
	this->List_index--;
}
