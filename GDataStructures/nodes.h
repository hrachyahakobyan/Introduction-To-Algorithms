#pragma once

template <typename T>
struct Node{
	Node<T>* next;
	T val;
};

template<typename T>
struct Leaf{
	Leaf<T>* l;
	Leaf<T>* r;
	Leaf<T>* p;
	T val;
	Leaf() : l(NULL), r(NULL){};
	~Leaf(){}
};

template<typename T>
struct LeafLCRS{
	LeafLCRS<T>* lc;
	LeafLCRS<T>* rs;
	T val;
	LeafLCRS() : lc(NULL), rs(NULL){};
	~LeafLCRS() {};
};