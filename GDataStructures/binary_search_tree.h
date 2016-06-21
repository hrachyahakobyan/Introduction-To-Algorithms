#pragma once
#include "binary_tree.h"

template<typename T>
class binary_search_tree : binary_tree<T>
{
public:
	binary_search_tree() : binary_tree<T>(){}
	~binary_search_tree() { destroy(); }
	 void insert(const T& val) ;
	 void remove(Leaf<T>* leaf) ;
	 Leaf<T>* search(const T& val, bool iter = false) const ;
	 Leaf<T>* max(bool rec = false, Leaf<T>* node = NULL) const ;
	 Leaf<T>* min(bool rec = false, Leaf<T>* node = NULL) const ;
	 Leaf<T>* successor(Leaf<T>* node) const ;
	 Leaf<T>* predecessor(Leaf<T>* node) const ;
	 void test() ;
	 void transplant(Leaf<T>* u, Leaf<T>* v, bool detach_v = false, bool update_children = false);
protected:
	 Leaf<T>* _min_iter(Leaf<T>* node) const ;
	 Leaf<T>* _max_iter(Leaf<T>* node) const ;
	 Leaf<T>* _min_rec(Leaf<T>* node) const ;
	 Leaf<T>* _max_rec(Leaf<T>* node) const ;
	 Leaf<T>* _search(Leaf<T>* leaf, const T& val) const ;
	 Leaf<T>* _search_iter(Leaf<T>* leaf, const T& val) const ;
	 void _insert(const T& val, Leaf<T>* leaf) ;
};



template<typename T>
void binary_search_tree<T>::remove(Leaf<T>* z)
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
void binary_search_tree<T>::insert(const T& val){
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
void binary_search_tree<T>::_insert(const T& val, Leaf<T>* leaf){
	// insert at left subtree
	if (val < leaf->val){
		// check if left subtree exists
		if (leaf->l != NULL){
			_insert(val, leaf->l);
		}
		else { //create the left subtree
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
void binary_search_tree<T>::transplant(Leaf<T>* u, Leaf<T>* v, bool detach_v, bool update_children)
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
Leaf<T>* binary_search_tree<T>::search(const T& val, bool iter) const
{
	if (!iter)
		return _search(root, val);
	else
		return _search_iter(root, val);
}

template<typename T>
Leaf<T>* binary_search_tree<T>::_search(Leaf<T>* root, const T& val) const
{
	if (root == NULL || val == root->val)
		return root;
	if (val < root->val)
		return _search(root->l, val);
	else
		return _search(root->r, val);
}

template<typename T>
Leaf<T>* binary_search_tree<T>::_search_iter(Leaf<T>* leaf, const T& val) const
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
Leaf<T>* binary_search_tree<T>::min(bool rec, Leaf<T>* node) const
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
Leaf<T>* binary_search_tree<T>::max(bool rec, Leaf<T>* node) const
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
Leaf<T>* binary_search_tree<T>::_min_iter(Leaf<T>* node) const
{
	while (node && node->l != NULL)
		node = node->l;
	return node;
}

template<typename T>
Leaf<T>* binary_search_tree<T>::_max_iter(Leaf<T>* node) const
{
	while (node && node->r != NULL)
		node = node->r;
	return node;
}

template<typename T>
Leaf<T>* binary_search_tree<T>::_min_rec(Leaf<T>* node) const
{
	if (!node || node->l == NULL)
		return node;
	else
		return _min_rec(node->l);
}

template<typename T>
Leaf<T>* binary_search_tree<T>::_max_rec(Leaf<T>* node) const
{
	if (!node || node->r == NULL)
		return node;
	else
		return _max_rec(node->r);
}

template<typename T>
Leaf<T>* binary_search_tree<T>::successor(Leaf<T>* node) const
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
Leaf<T>* binary_search_tree<T>::predecessor(Leaf<T>* node) const
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
void binary_search_tree<T>::test(){
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
					std::cout << std::endl;
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






