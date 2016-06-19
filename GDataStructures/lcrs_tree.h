#pragma once
#include "nodes.h"
template<typename T>
class lcrs_tree
{
public:
	lcrs_tree() : root(NULL){};
	~lcrs_tree(){ destroy(); }
	void insert(const T& val);
	void print() const;
	void destroy();
private:
	typedef LeafLCRS<T> Leaf;
	Leaf* root; 
	void insert(const T& val, Leaf* leaf);
	void destroy(Leaf* leaf);
	void print(Leaf* leaf) const;
};

template<typename T>
void lcrs_tree<T>::destroy()
{
	destroy(root);
}

template<typename T>
void lcrs_tree<T>::insert(const T& val)
{
	if (root != NULL){
		insert(val, root);
	}
	else {
		root = new Leaf;
		root->val = val;
	}
}

template<typename T>
void lcrs_tree<T>::print() const {
	print(root);
}

template<typename T>
void lcrs_tree<T>::insert(const T& val, Leaf* leaf)
{
	if (val < leaf->val){
		if (leaf->lc != NULL){
			insert(val, leaf->lc);
		}
		else {
			leaf->lc = new Leaf;
			leaf->lc->val = val;
		}
	}
	else {
		if (leaf->rs != NULL){
			insert(val, leaf->rs);
		}
		else {
			leaf->rs = new Leaf;
			leaf->rs->val = val;
		}
	}
}

template<typename T>
void lcrs_tree<T>::destroy(Leaf* leaf)
{
	if (leaf->lc){
		destroy(leaf->lc);
	}
	if (leaf->rs){
		destroy(leaf->rs);
	}
	delete leaf;
	leaf = NULL;
}


template<typename T>
void lcrs_tree<T>::print(Leaf* leaf) const {
	if (leaf == NULL)
		return;
	if (leaf->lc){
		print(leaf->lc);
	}
	std::cout << leaf->val << std::endl;
	if (leaf->rs){
		print(leaf->rs);
	}
}