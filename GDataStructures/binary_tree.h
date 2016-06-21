#pragma once
#include "nodes.h"


template<typename T>
class binary_tree
{
public:
	binary_tree() : root(NULL){};
	virtual ~binary_tree() { destroy(); }
    void destroy();

	// Pure virtual methods
	virtual void insert(const T& val) = 0;
	virtual void remove(Leaf<T>* leaf) = 0;
	virtual Leaf<T>* search(const T& val, bool iter = false) const = 0;
	virtual Leaf<T>* max(bool rec = false, Leaf<T>* node = NULL) const = 0;
	virtual Leaf<T>* min(bool rec = false, Leaf<T>* node = NULL) const = 0;
	virtual Leaf<T>* successor(Leaf<T>* node) const = 0;
	virtual Leaf<T>* predecessor(Leaf<T>* node) const = 0;
	virtual void test() = 0;

	// Implemented methods
	int height() const;
	int height(Leaf<T>* leaf) const;
	int count() const;
	int count(Leaf<T>* leaf) const;

	void printPretty(Leaf<T> *node = NULL, int level = 1, int indentSpace = 0, std::ostream& out = std::cout) const;
	void print_inOrder(bool iter = false, bool use_stack = false) const;
	void print_postOrder() const;
	void print_preOrder() const;

protected:
	Leaf<T>* root;

	// Pure virtual methods
	virtual Leaf<T>* _min_iter(Leaf<T>* node) const = 0;
	virtual Leaf<T>* _max_iter(Leaf<T>* node) const = 0;
	virtual Leaf<T>* _min_rec(Leaf<T>* node) const = 0;
	virtual Leaf<T>* _max_rec(Leaf<T>* node) const = 0;
	virtual Leaf<T>* _search(Leaf<T>* leaf, const T& val) const = 0;
	virtual Leaf<T>* _search_iter(Leaf<T>* leaf, const T& val) const = 0;
	virtual void _insert(const T& val, Leaf<T>* leaf) = 0;

	// Implemented methods
	virtual void _destroy(Leaf<T>* leaf);
	void _print_inOrder_recursive(Leaf<T>* leaf) const;
	void _print_inOrder_iterative_stack(Leaf<T>* leaf) const;
	void _print_inOrder_iterative_noStack(Leaf<T>* leaf) const;
	void _print_postOrder(Leaf<T>* leaf, int indent = 0) const;
	void _print_preOrder(Leaf<T>* leaf) const;

	// Helpers
	std::string intToString(int a) const;
	bool isLeaf(Leaf<T>* leaf) const;
	void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Leaf<T>*>& nodesQueue, std::ostream& out) const;
	void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Leaf<T>*>& nodesQueue, std::ostream& out) const;
	void printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Leaf<T>*>& nodesQueue, std::ostream& out) const;
	void printNodeInfo(Leaf<T>* node) const;
};

template<typename T>
void binary_tree<T>::destroy(){
	_destroy(root);
}

template<typename T>
void binary_tree<T>::_destroy(Leaf<T>* leaf){
	if (leaf != NULL){
		_destroy(leaf->l);
		_destroy(leaf->r);
		delete leaf;
		leaf = NULL;
	}
}

template<typename T>
void binary_tree<T>::print_inOrder(bool iter, bool stack) const{
	if (!iter)
		_print_inOrder_recursive(root);
	else if (iter && stack)
		_print_inOrder_iterative_stack(root);
	else
		_print_inOrder_iterative_noStack(root);
}

template<typename T>
void binary_tree<T>::_print_inOrder_recursive(Leaf<T>* leaf) const{
	if (leaf == NULL)
		return;
	if (leaf->l != NULL)
		_print_inOrder_recursive(leaf->l);
	std::cout << leaf->val << std::endl;
	if (leaf->r != NULL)
		_print_inOrder_recursive(leaf->r);
}

template<typename T>
void binary_tree<T>::_print_inOrder_iterative_stack(Leaf<T>* root) const{
	auto r = root;
	std::stack<Leaf<T>*> stack;
	bool done = false;
	while (done == false)
	{
		if (r != NULL)
		{
			stack.push(r);
			r = r->l;
		}
		else
		{
			if (!stack.empty())
			{
				r = stack.top();
				stack.pop();
				std::cout << r->val << std::endl;
				r = r->r;
			}
			else {
				done = true;
			}
		}
	}
}

template<typename T>
void binary_tree<T>::_print_inOrder_iterative_noStack(Leaf<T>* root) const
{
	// this is essentially the same as 
	// 1. find the minimum
	// 2. find the successors why you are out of them
	// so we could rewrite in a more elegant way
	auto node = root;
	if (node != NULL)
		node = min(true, node);
	while (node){
		std::cout << node->val << ' ';
		node = successor(node);
	}


	/*auto node = root;
	if (node != NULL){
		while (node->l != NULL){
			node = node->l;
		}
		while (node != NULL){
			std::cout << node->val << std::endl;
			if (node->r != NULL){
				node = node->r;
				while (node->l != NULL){
					node = node->l;
				}
			}
			else {
				while (node->p != NULL && node->p->r == node){
					node = node->p;
				}
				node = node->p;
			}
		}
	}*/
}

template<typename T>
void binary_tree<T>::print_postOrder() const
{
	_print_postOrder(root);
}

template<typename T>
void binary_tree<T>::_print_postOrder(Leaf<T>* leaf, int indent) const
{
	if (leaf){
		if (leaf->l != NULL)
			_print_postOrder(leaf->l, indent + 2);
		if (leaf->r != NULL)
			_print_postOrder(leaf->r, indent + 2);
		std::cout << leaf->val << ' ';
	}
}

template<typename T>
void binary_tree<T>::print_preOrder() const
{
	_print_preOrder(root);
}

template<typename T>
void binary_tree<T>::_print_preOrder(Leaf<T>* leaf) const
{
	if (leaf){
		std::cout << leaf->val << std::endl;
		if (leaf->l != NULL)
			_print_preOrder(leaf->l);
		if (leaf->r != NULL)
			_print_preOrder(leaf->r);
	}
}

template<typename T>
int binary_tree<T>::height() const
{
	return height(root);
}

template<typename T>
int binary_tree<T>::height(Leaf<T>* leaf) const
{
	if (!leaf)
		return 0;
	return 1 + std::max(height(leaf->r), height(leaf->l));
}

// Helpers

template<typename T>
bool binary_tree<T>::isLeaf(Leaf<T>* leaf) const{
	return (leaf && !leaf->r && !leaf->l);
}

template<typename T>
void binary_tree<T>::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Leaf<T>*>& nodesQueue, std::ostream& out) const {
	std::deque<Leaf<T>*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++) {
		out << ((i == 0) ? std::setw(startLen - 1) : std::setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
		out << std::setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
	}
	out << std::endl;
}

template<typename T>
void binary_tree<T>::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Leaf<T>*>& nodesQueue, std::ostream& out) const {
	std::deque<Leaf<T>*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->r) ? std::setfill('_') : std::setfill(' '));
		out << std::setw(branchLen + 2) << ((*iter) ? std::to_string((*iter)->val) : "");
		out << ((*iter && (*iter)->r) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
	}
	out << std::endl;
}


template<typename T>
void binary_tree<T>::printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Leaf<T>*>& nodesQueue, std::ostream& out) const {
	std::deque<Leaf<T>*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? std::setw(indentSpace + 2) : std::setw(2 * level + 2)) << ((*iter) ? std::to_string((*iter)->val) : "");
	}
	out << std::endl;
}


template<typename T>
void binary_tree<T>::printPretty(Leaf<T> *node , int level, int indentSpace, std::ostream& out) const {
	if (node == NULL)
		node = this->root;
	int h = height(node);
	int nodesInThisLevel = 1;

	int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level)*(int)pow(2.0, h - 1);  // eq of the length of branch for each node of each level
	int nodeSpaceLen = 2 + (level + 1)*(int)pow(2.0, h);  // distance between r neighbor node's r arm and r neighbor node's r arm
	int startLen = branchLen + (3 - level) + indentSpace;  // starting space to the first node to print of each level (for the r most node of each level only)

	std::deque<Leaf<T>*> nodesQueue;
	nodesQueue.push_back(node);
	for (int r = 1; r < h; r++) {
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
		branchLen = branchLen / 2 - 1;
		nodeSpaceLen = nodeSpaceLen / 2 + 1;
		startLen = branchLen + (3 - level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

		for (int i = 0; i < nodesInThisLevel; i++) {
			Leaf<T> *currNode = nodesQueue.front();
			nodesQueue.pop_front();
			if (currNode) {
				nodesQueue.push_back(currNode->l);
				nodesQueue.push_back(currNode->r);
			}
			else {
				nodesQueue.push_back(NULL);
				nodesQueue.push_back(NULL);
			}
		}
		nodesInThisLevel *= 2;
	}
	printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
	printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

template<typename T>
std::string binary_tree<T>::intToString(int val) const {
	std::ostringstream ss;
	ss << val;
	return ss.str();
}

template<typename T>
void binary_tree<T>::printNodeInfo(Leaf<T>* node) const
{
	if (node == NULL){
		std::cout << "NULL" << std::endl;
	}
	else {
		std::cout << "Value " << node->val << std::endl;
		if (node->p){
			std::cout << "Parent " << node->p->val << std::endl;
		}
		else {
			std::cout << "No parent.\n";
		}
		if (node->l){
			std::cout << "Left child " << node->l->val << std::endl;
		}
		else {
			std::cout << "No left child.\n";
		}
		if (node->r){
			std::cout << "Right child " << node->r->val << std::endl;
		}
		else {
			std::cout << "No right child.\n";
		}
	}
}

template<typename T>
int binary_tree<T>::count() const{
	return count(root);
}

template<typename T>
int binary_tree<T>::count(Leaf<T>* leaf) const{
	if (leaf == NULL)
		return 0;
	return 1 + count(leaf->r) + count(leaf->l);
}