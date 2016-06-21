// GSorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Determines if there exist 2 elements in vec whose sum is equal to x

template<typename T>
bool exist_sum(const std::vector<T>& vec, const T& val)
{
	if (vec.size() < 2)
		return false;
	else if (vec.size() == 2)
		return (vec[0] + vec[1] == val);
	auto cvec = vec;
	merge_sort(cvec, 0, cvec.size() - 1);
	std::vector<T>::const_reverse_iterator backIt = cvec.rbegin();
	std::vector<T>::const_iterator frontIt = cvec.begin();
	while (backIt.base() - 1 != frontIt)
	{
		T sum = *backIt + *frontIt;
		if (sum == val)
			return true;
		else if (sum < val)
			frontIt++;
		else
			backIt++;
	}
	return false;
}

template<typename T>
T* binary_search(std::vector<T>& vec, const T& val, int l, int h)
{
	if (l > h)
		return false;
	int m = (h + l) / 2;
	if (vec[m] == val)
		return &vec[m];
	else if (vec[m] > val)
		return binary_search(vec, val, l, m - 1);
	else
		return binary_search(vec, val, m + 1, h);
}

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

template<typename T>
void merge_sort(std::vector<T>& C, int p, int r, bool use_insertion = false, int insertion_thresh = 20)
{
	if ((r - p) <= insertion_thresh){
		insertion_sort(C);
	}
	else if (p < r){ 
		int q = p + (r - p) / 2;
		merge_sort(C, p, q);
		merge_sort(C, q + 1, r);
		merge(C, p, q, r);
	}
}

template<typename T>
void merge(std::vector<T>& C, int p, int q, int r)
{
	std::cout << "p " << p << "q " << q << "r " << r << std::endl;
	std::vector<T> L(C.begin() + p, C.begin() + q + 1);
	std::vector<T> R(C.begin() + q + 1, C.begin() + r + 1);

	//std::vector<T> L(q - p + 1);
	//std::vector<T> R(r - q);
	/*for (int i = 0; i < q - p + 1; i++){
		L[i] = C[p + i];
	}
	for (int i = 0; i < r - q; i++){
		R[i] = C[q + i + 1];
	}*/
	std::size_t li = 0;
	std::size_t ri = 0;
	std::size_t k = p;
	while (li < L.size() && ri < R.size()){
		if (L[li] <= R[ri])
		{
			C[k] = L[li];
			li++; 
		}
		else
		{
			C[k] = R[ri];
			ri++; 
		}
		k++;
	}
	while (li < L.size())
	{
		C[k] = L[li];
		li++; k++;
	}
	while (ri < R.size())
	{
		C[k] = R[ri];
		ri++; k++;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> C = { {1, 9, 8, 1, 4, 5, 1, 7, 4, 8, 2,5, 0, -1, 0, 2, 4, 5, 6,4 ,3, 4, 5, 9 ,1, 9} };
	merge_sort(C, 0, C.size() - 1, true, 5);
	for (auto it = C.begin(); it != C.end(); it++)
		std::cout << *it << ' ';
	return 0;
}

