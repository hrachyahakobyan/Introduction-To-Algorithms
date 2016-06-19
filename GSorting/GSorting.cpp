// GSorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
template<typename T>
void insertion_sort(std::vector<T>& arr, bool asc = true)
{
	if (arr.size() < 1)
		return;
	for (std::size_t j = 1; j < arr.size(); j++)
	{
		T key = arr[j];
		int i = j - 1;
		while (i >= 0 && (asc ? (arr[i] > key) : (arr[i] < key ))){
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = key;
	}
}

template<typename T>
void selection_sort(std::vector<T>& arr, bool asc = true)
{
	if (arr.size() < 1)
		return;
	for (std::size_t j = 0; j < arr.size() - 1; j++)
	{
		std::size_t m_index = j;
		for (std::size_t i = j + 1; i < arr.size(); i++)
		{
			if (((arr[i] < arr[m_index]) && asc) || (!asc && (arr[i] > arr[m_index])))
			{
				m_index = i;
			}
		}
		T temp = arr[j];
		arr[j] = arr[m_index];
		arr[m_index] = temp;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> arr = { { 12, 13, 15, 0} };
	selection_sort(arr, false);
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	return 0;
}

