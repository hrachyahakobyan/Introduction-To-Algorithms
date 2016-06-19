#pragma once
#include "nodes.h"

template<typename T>
class gstack_list
{
public:
	void push(const T& t);
	void pop();
	T top() const;
	bool empty() const;
	gstack_list() : head(NULL){}
	~gstack_list(){
		while (head != NULL)
		{
			auto temp = head;
			head = head->next;
			delete temp;
		}
	}
private:
	Node<T>* head;
};


template<typename T>
void gstack_list<T>::push(const T& t)
{
	Node<T>* n = new Node<T>;
	n->val = t;
	n->next = head;
	head = n;
}

template<typename T>
void gstack_list<T>::pop()
{
	auto temp = head;
	head = head->next;
	delete temp;
	temp = NULL;
}

template<typename T>
T gstack_list<T>::top() const
{
	assert(head != NULL && "ERROR");
	return head->val;
}

template<typename T>
bool gstack_list<T>::empty() const
{
	return head == NULL;
}