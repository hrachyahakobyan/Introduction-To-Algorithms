// GDataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gqueue_stack.h"
#include "gstack_queue.h"
#include "gstack_list.h"
#include "gqueue_list.h"
#include "binary_search_tree.h"
#include "lcrs_tree.h"

void printOrderedPairs(std::string nums, std::string pref = "")
{
	std::cout << pref << '(' << nums << ')' << std::endl;
	for (int i = 1; i < nums.size(); i++){
		std::string npref = pref;
		npref.append("(");
		npref.append(nums.substr(0, i));
		npref.append(")");
		printOrderedPairs(nums.substr(i, nums.size() - i), npref);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[11] = { 30, 20, 40, 10, 25, 35, 50, 5, 15, 28, 41 };
	binary_search_tree<int> tree;
	for (int i = 0; i < 11; i++)
		tree.insert(arr[i]);
	tree.test();
	//std::string nums("1234");
	//printOrderedPairs(nums);
	return 0;
}
