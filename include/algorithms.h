#pragma once

#include <stdexcept>
/*
  Merge sort algorithm , if any function pointer is provided. The algorithm will sort  in ascending order.
  That means that can have undefined behaviour if we use it with user classes. In that case it is better to retrive 
  a function that tells how to compare the elements, cause user define objects can't be compare as a primitive data
  types, cause we can't assume what should be compare, and what means one object be greater than the other or lesser.

  @autor Aitor sanmartin ferreira
*/

namespace asf {
	//typedefs
	template<typename T>
	using fptr_predicate = bool(*)(const T&a, const T&b);

	//merge function
	template<typename T>
	void merge(T*L, T*array, T* R, int size, int l_size, int r_size, fptr_predicate<T> func) {

		int l_i{}, r_i{}, m_i{};

		// if we pass a valid predicate to compare we use it else we use the less < operator to sort
		if (func != nullptr) {

			while (l_i < l_size && r_i < r_size) {

				if (func(L[l_i], R[r_i])) {
					array[m_i] = L[l_i];
					++l_i;

				}
				else {
					array[m_i] = R[r_i];
					++r_i;
				}
				++m_i;
			}
		}
		else {//default way to sort

			if (L[l_i] < R[r_i]) {
				array[m_i] = L[l_i];
				++l_i;
			}
			else {
				array[m_i] = R[r_i];
				++r_i;
			}
			++m_i;
		}

		while (l_i < l_size) {
			array[m_i] = L[l_i];
			++l_i;
			++m_i;
		}
		while (r_i < r_size) {
			array[m_i] = R[r_i];
			++r_i;
			++m_i;
		}

	}

	// merge sort
	template <typename T>
	void merge_sort(T* array, int size, fptr_predicate<T> func) {

		if (size > 1) {

			int l_size = size / 2;
			int r_size = size - l_size;

			T* Left = nullptr;
			T* Right = nullptr;
			try {

				Left = new T[l_size];
				Right = new T[r_size];

			}
			catch (std::bad_alloc& e) {
				delete[] Left;
				delete[] Right;
				Left = nullptr;
				Right = nullptr;
				std::cout << e.what() << std::endl;
			}
			for (int i = 0; i < l_size; ++i) {
				Left[i] = array[i];
			}
			for (int i = l_size; i < size; ++i) {
				Right[i - l_size] = array[i];
			}
			merge_sort(Left, l_size, func);
			merge_sort(Right, r_size, func);
			merge(Left, array, Right, size, l_size, r_size, func);
			delete[]Left;
			delete[]Right;
		}

	}
}