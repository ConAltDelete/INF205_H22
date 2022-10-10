#ifndef DDLN
#define DDLN

#include <iostream>
#include "sequence.h"

namespace seq {

struct DLLNode {
	int* value = nullptr;
	DLLNode* nptr = nullptr;
	DLLNode* pptr = nullptr;
};

class DoublyLinkedList: public Sequence {
	DLLNode* current_node = nullptr;

	int List_index = 0;

	DLLNode* Front = current_node;
	DLLNode* Back = current_node;
	int List_size = 0;

	public:

	void go_to(int i);

	bool empty() const;
	size_t size() const;
	size_t index();

	int& front();
	int& back();

	int& at(int i);

	void push(const int& pushed_item);
	void push_front(const int& pushed_item);

	void push_back(const int& pushed_item);

	void pop();
	void pop_front();
	void pop_back();
	void clear();

	void insert_at(int i, const int& inserted_item);
	void erase_at(int i);
};
}
#endif
