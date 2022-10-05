#include <iostream>
#include "sequence.h"

using namespace seq;

class DoublyLinkedList: public Sequence {
	DLLNode* current_node = nullptr;

	int index = 0;

	DLLNode* Front = current_node;
	DLLNode* Back = current_node;
	int size = 0;

	public:

	void go_to(int i){
		if(this->current_node->index < i){
			DLLNode* at_node = this->current_node;
			while(this->index != i){
				at_node = at_node->pptr;
				this->index--;
			}
			this->current_node = at_node;
		} else if(this->current_node->index > i){
			DLLNode* at_node = this->current_node;
			while(this->index != i){
				at_node = at_node->nptr;
				this->index++;
			}
			this->current_node = at_node;
		}
	}

	bool empty(){
		return this->size == 0;
	}
	size_t size(){
		return this->size;
	}
	size_t index(){
		return this->index;
	}

	int& front() {
		return this->Front->value;
	}
	int& back(){
		return this->Back->value;
	}

	int& at(int i){
		if(this->index == i){
			return this->current_node->value;
		}

		this->go_to(i);
		return this->current_node->value;

	};

	void push(const int& pushed_item){
		this->push_front(pushed_item);
	}
	void push_front(const int& pushed_item){
		if(current_node == nullptr){
			DDLNode* current_node = new DLLNode()
			current_node->value = pushed_item;
			this->current_node = current_node;
			this->size++;
		} else {
			DLLNode* new_node = new DLLNode();
			new_node->value = pushed_item;
			new_node->pptr = this->Front;
			this->Front->nptr = new_node;
			this->Front = new_node;
			this->size++;
		}
	}

	void push_back(const int& pushed_item){
		if(this->current_node == nullptr){
			DDLNode* current_node = new DLLNode()
			current_node->value = pushed_item;
			this->current_node = current_node;
			this->size++;
		} else {
			DLLNode* new_node = new DLLNode();
			new_node->value = pushed_item;
			new_node->nptr = this->Back;
			this->Back->pptr = new_node;
			this->size++;
			this->Back = new_node;
			this->index++;
		}
	}


	void pop(){this->pop_front()}
	void pop_front(){
		if(this->current_node == this->Front && this->current_node->pptr != nullptr){
			this->current_node = this->current_node->pptr;
			this->index--;
		}
		if(this->Front != nullptr){
			DLLNode* placeholder = this->Front->pptr;
			placeholder->nptr = nullptr;
			delete this->Front;
			this->Front = placeholder;
		}
	}
	void pop_back(){
		if(this->current_node == this->Back && this->current_node->nptr != nullptr){
			this->current_node = this->current_node->nptr;
			this->index++;
		}

		if(this->Back != nullptr){
			DLLNode* placeholder = this->Back->nptr;
			placeholder->pptr = nullptr;
			delete this->Back;
			this->Back = placeholder;
		}
	}
	void clear(){
		/*
		 * 1) set position to Front or Back
		 * 2) pop until size == 1
		 * 3) delete value at index 0
		 * 4) profit
		 * */

	}

	void insert_at(int i, const int& inserted_item){
		this->go_to(i);
		DLLNode* new_node = new DLLNode();
		new_node->value = inserted_item;
		new_node->pptr = this->current_node->pptr;
		new_node->nptr = this->current_node;

		this->current_node->pptr->nptr = new_node;
		this->current_node->pptr = new_node;
		this->index++;
	}
	void erase_at(int i){
		DLLNode* prob_node;
		
		this->go_to(i);

		prob_node = this->current_node;

		prob_node->pptr->nptr = prob_node->nptr;
		prob_node->nptr->pptr = prob_node->pptr;
		this->current_node = prob_node->pptr;
		delete prob_node;
		this->size--;
		this->index--;
	}
};

struct DLLNode {
	int* value = nullptr;
	void* nptr = nullptr;
	void* pptr = nullptr;
};
