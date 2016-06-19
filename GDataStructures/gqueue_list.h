#pragma once
#include "nodes.h"
template<typename T>
class gqueue_list
{
public:
	gqueue_list() : head(NULL), tail(NULL){}
	~gqueue_list(){
		while (head != NULL)
		{
			auto temp = head;
			head = head->next;
			delete temp;
		}
	}
	void enqueue(const T& t);
	T dequeue();
	bool empty() const;
private:
	Node<T>* head;
	Node<T>* tail;
};

template<typename T>
void gqueue_list<T>::enqueue(const T& t)
{
	Node<T>* n = new Node<T>;
	n->val = t;
	if (tail != NULL)
		tail->next = n;
	tail = n;
	if (head == NULL)
		head = tail;
}

template<typename T>
T gqueue_list<T>::dequeue()
{
	assert(head != NULL && "ERROR");
	T val = head->val;
	if (head == tail)
	{
		delete head;
		tail = NULL;
		head = NULL;
		return val;
	}
	auto temp = head;
	head = head->next;
	delete temp;
	return val;
}

template<typename T>
bool gqueue_list<T>::empty() const
{
	return head == NULL;
}