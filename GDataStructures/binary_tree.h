#pragma once
#include "nodes.h"


template<typename T>
class binary_tree
{
public:
	binary_tree() : root(NULL){};
	~binary_tree() { destroy(); }
	void destroy();
	void insert(const T& val);
	void remove(Leaf<T>* leaf);
	void transplant(Leaf<T>* u, Leaf<T>* v, bool detach_v = false, bool update_children = false);
	Leaf<T>* search(const T& val, bool iter = false) const;
	void printPretty(Leaf<T> *node = NULL, int level = 1, int indentSpace = 0, std::ostream& out = std::cout) const;
	void print_inOrder(bool iter = false, bool use_stack = false) const;
	void print_postOrder() const;
	void print_preOrder() const;
	Leaf<T>* max(bool rec = false, Leaf<T>* node = NULL) const;
	Leaf<T>* min(bool rec = false, Leaf<T>* node = NULL) const;
	Leaf<T>* successor(Leaf<T>* node) const;
	Leaf<T>* predecessor(Leaf<T>* node) const;
	int height() const;
	int height(Leaf<T>* leaf) const;
	int count() const;
	int count(Leaf<T>* leaf) const;
	void test();
private:
	Leaf<T>* root;
	Leaf<T>* _min_iter(Leaf<T>* node) const;
	Leaf<T>* _max_iter(Leaf<T>* node) const;
	Leaf<T>* _min_rec(Leaf<T>* node) const;
	Leaf<T>* _max_rec(Leaf<T>* node) const;
	Leaf<T>* _search(Leaf<T>* leaf, const T& val) const;
	Leaf<T>* _search_iter(Leaf<T>* leaf, const T& val) const;
	void _insert(const T& val, Leaf<T>* leaf);
	void _destroy(Leaf<T>* leaf);
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
void binary_tree<T>::remove(Leaf<T>* z)
{
	if (z == NULL)
		return;
	if (z->l == NULL){
		transplant(z, z->r);
		delete z;
		z = NULL;
	}
	else if (z->r == NULL){
		transplant(z, z->l);
		delete z;
		z = NULL;
	}
	else {
		Leaf<T>* y = min(false, z->r);
		if (y->p != z){
			transplant(y, y->r);

			y->r = z->r;
			y->r->p = y;
		}
		transplant(z, y);
		y->l = z->l;
		y->l->p = y;
		delete z;
		z = NULL;
	}
}

template<typename T>
void binary_tree<T>::insert(const T& val){
	if (root == NULL)
	{
		root = new Leaf<T>;
		root->val = val;
		root->p = NULL;
	}
	else {
		_insert(val, root);
	}
}
// Replace u with v
// Use with caution! Transplanted subtree is not being destroyed.
template<typename T>
void binary_tree<T>::transplant(Leaf<T>* u, Leaf<T>* v, bool detach_v, bool update_children)
{
	if (u == NULL)
		return;
	if (u->p == NULL){
		root = v;
	}
	else if (u->p->l == u){
		u->p->l = v;
	}
	else {
		u->p->r = v;
	}
	if (update_children){
		v->l = u->l;
		v->r = u->r;
	}
	// detach v from previous parent
	if (v != NULL)
	{
		if (detach_v){
			if (v->p->l == v)
				v->p->l = NULL;
			else
				v->p->r = NULL;
		}
		v->p = u->p;
	}
	//u->p = NULL;
}

template<typename T>
void binary_tree<T>::_insert(const T& val, Leaf<T>* leaf){
	// insert at left subtree
	if (val < leaf->val){
		// check if left subtree exists
		if (leaf->l != NULL){
			_insert(val, leaf->l);
		} else { //create the left subtree
			leaf->l = new Leaf<T>;
			leaf->l->val = val;
			leaf->l->p = leaf;
		}
	}
	else if (val >= leaf->val){
		// check if right subtree exists
		if (leaf->r != NULL){
			_insert(val, leaf->r);
		}
		else { //create the right subtree
			leaf->r = new Leaf<T>;
			leaf->r->val = val;
			leaf->r->p = leaf;
		}
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
Leaf<T>* binary_tree<T>::search(const T& val, bool iter) const
{
	if (!iter)
		return _search(root, val);
	else
		return _search_iter(root, val);
}

template<typename T>
Leaf<T>* binary_tree<T>::_search(Leaf<T>* root, const T& val) const
{
	if (root == NULL || val == root->val)
		return root;
	if (val < root->val)
		return _search(root->l, val);
	else
		return _search(root->r, val);
}

template<typename T>
Leaf<T>* binary_tree<T>::_search_iter(Leaf<T>* leaf, const T& val) const
{
	while (leaf != NULL && leaf->val != val){
		if (leaf->val < val)
			leaf = leaf->r;
		else
			leaf = leaf->l;
	}
	return leaf;
}

template<typename T>
Leaf<T>* binary_tree<T>::min(bool rec, Leaf<T>* node) const
{
	if (!node){
		node = root;
	}
	if (rec){
		return _min_rec(node);
	}
	else {
		return _min_iter(node);
	}
}

template<typename T>
Leaf<T>* binary_tree<T>::max(bool rec, Leaf<T>* node) const
{
	if (!node){
		node = root;
	}
	if (rec){
		return _max_rec(node);
	}
	else {
		return _max_iter(node);
	}
}

template<typename T>
Leaf<T>* binary_tree<T>::_min_iter(Leaf<T>* node) const
{
	while (node && node->l != NULL)
		node = node->l;
	return node;
}

template<typename T>
Leaf<T>* binary_tree<T>::_max_iter(Leaf<T>* node) const
{
	while (node && node->r != NULL)
		node = node->r;
	return node;
}

template<typename T>
Leaf<T>* binary_tree<T>::_min_rec(Leaf<T>* node) const
{
	if (!node || node->l == NULL)
		return node;
	else
		return _min_rec(node->l);
}

template<typename T>
Leaf<T>* binary_tree<T>::_max_rec(Leaf<T>* node) const
{
	if (!node || node->r == NULL)
		return node;
	else
		return _max_rec(node->r);
}

template<typename T>
Leaf<T>* binary_tree<T>::successor(Leaf<T>* node) const
{
	if (node == NULL)
		return NULL;
	if (node->r != NULL)
		return min(true, node->r);
	while (node->p != NULL && node->p->r == node)
		node = node->p;
	node = node->p;
	return node;
}

template<typename T>
Leaf<T>* binary_tree<T>::predecessor(Leaf<T>* node) const
{
	if (node == NULL)
		return NULL;
	if (node->l != NULL)
		return max(true, node->l);
	while (node->p != NULL && node->p->l == node)
		node = node->p;
	node = node->p;
	return node;
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

template<typename T>
void binary_tree<T>::test(){
	std::string info = "Enter '0' to exit.\nEnter '1' to print info.\n";
	info.append("Enter '2' to search a node.\n");
	info.append("Enter '3' to insert a new node.\n");
	info.append("Enter '4' to remove a node.\n");
	info.append("Enter '5' to transplant a node.\n");
	info.append("Enter '6' to find successor of a node.\n");
	info.append("Enter '7' to find predecessor of a node.\n");
	info.append("Enter '8' to print in order.\n");
	info.append("Enter '9' to print pre order.\n");
	info.append("Enter '10' to print post order.\n");
	info.append("Enter '11' to print pretty.\n");
	info.append("Etner '12' to print information about the tree.\n");
	std::cout << info << std::endl;
	while (true){
		std::cout << "Command>>";
		int a;
		std::cin >> a;
		if (a == 0){
			std::cout << "Exiting test.\n";
			break;
		}
		else if (a == 1){
			std::cout << info << std::endl;
		}
		else if (a == 2) {
			std::cout << "Searching for a node. Enter the value to search.\n";
			std::cout << "Node>>";
			T val;
			std::cin >> val;
			std::cout << "Searching for a node with value " << val << ".\n";
			Leaf<T>* node = search(val);
			if (node != NULL){
				std::cout << "Node found.\n";
				printNodeInfo(node);
				std::cout << "\n.";
			}
			else {
				std::cout << "Node not found.\n";
			}
		}
		else if (a == 3){
			std::cout << "Inserting a node. Enter the new node value.\n";
			std::cout << "Node>>";
			T val;
			std::cin >> val;
			insert(val);
			std::cout << "Inserted a new node with value " << val << ".\n";
			printPretty();
		}
		else if (a == 4){
			std::cout << "Removing a node. Enter the value to remove the node.\n";
			std::cout << "Node>>";
			T val;
			std::cin >> val;
			Leaf<T>* leaf = search(val);
			if (leaf){
				remove(leaf);
				std::cout << "Removed the node with value " << val << ".\n";
				printPretty();
				std::cout << std::endl;
			}
			else {
				std::cout << "Node with value " << val << " not found.\n";
			}
		}
		else if (a == 5){
			std::cout << "Transplanting a node. Enter the node value to transplant, space, node value to transplant with.\n";
			T uv, vv;
			std::cout << "Node to transplant>>";
			std::cin >> uv;
			std::cout << std::endl;
			std::cout << "Node to transplant with>>";
			std::cin >> vv;
			std::cout << std::endl;
			Leaf<T>* u = search(uv);
			Leaf<T>* v = search(vv);
			if (!u || !v){
				std::cout << "Node to be transplanted and/or node to transplant with not found.\n";
			}
			else {
				transplant(u, v, true);
				_destroy(u);
				std::cout << "Transplanted node with value " << uv << " with a node with value " << vv << std::endl;
				printPretty();
			}
		}
		else if (a == 6){
			std::cout << "Finding the sucessor of a node. Enter the value of the node.\n";
			std::cout << "Node>>";
			T val;
			std::cin >> val;
			Leaf<T>* node = search(val);
			if (node == NULL){
				std::cout << "Node with value " << val << " not found.\n";
			}
			else {
				Leaf<T>* suc = successor(node);
				if (suc){
					std::cout << "Successor found\n";
					printNodeInfo(suc);
					std::cout<< std::endl;
				}
				else {
					std::cout << "Successor not found.\n";
				}
			}
		}
		else if (a == 7){
			std::cout << "Finding the predecessor of a node. Enter the value of the node.\n";
			std::cout << "Node>>";
			T val;
			std::cin >> val;
			Leaf<T>* node = search(val);
			if (node == NULL){
				std::cout << "Node with value " << val << " not found.\n";
			}
			else {
				Leaf<T>* pred = predecessor(node);
				if (pred){
					std::cout << "Predecessor found\n";
					printNodeInfo(pred);
					std::cout << std::endl;
				}
				else {
					std::cout << "Predecessor not found.\n";
				}
			}
		}
		else if (a == 8){
			std::cout << "Printing in order. \n";
			print_inOrder();
			std::cout << std::endl;
		} 
		else if (a == 9){
			std::cout << "Printing pre order. \n";
			print_preOrder();
			std::cout << std::endl;
		}
		else if (a == 10){
			std::cout << "Printing post order. \n";
			print_postOrder();
			std::cout << std::endl;
		}
		else if (a == 11){
			std::cout << "Printing pretty. \n";
			printPretty();
			std::cout << std::endl;
		}
		else if (a == 12){
			std::cout << "Information about the tree.\n";
			std::cout << "Count " << count() << std::endl;
			std::cout << "Maximum " << max(false)->val << std::endl;
			std::cout << "Minimum " << min(false)->val << std::endl;
			std::cout << "Height " << height() << std::endl;
		}
		else {
			std::cout << "Invalid command. Enter '1' to print info.\n";
		}
	}
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