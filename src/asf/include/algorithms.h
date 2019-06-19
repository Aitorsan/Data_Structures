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
  
template<typename T>
struct Sorter 
{ 
     using fptr_predicate = bool(*)(const T&a, const T&b);

     static void merge_sort(T* list, int beg, int end, fptr_predicate func = nullptr) 
     {
        if (beg < end) 
        {
           int middle = (beg + end) / 2 + 1;
	       merge_sort(list, beg, middle - 1, func);
	   	   merge_sort(list, middle, end, func);
           merge(list, beg, middle, end, func);
        }
     }
private:
      
    static void merge(T*list, int beg, int middle, int end, fptr_predicate func=[](const T& a , const T&b ){return a < b;})  
    { 
      	int l_it = beg;
	 	int r_it = middle;
        T* temp = nullptr;
	 	try 
	 	{
	 		temp = new T[end - beg + 1];
            int cont{};
            while (l_it < middle || r_it <= end) 
            {
			    //if we pass a valid predicate to compare we use it, else we use the less < operator to sort
				if (func != nullptr) 
				{
					if ( (r_it > end || l_it < middle) &&  func(list[l_it], list[r_it])) 
					{
						temp[cont] = list[l_it];
						++l_it;
					}
					else if ((l_it > middle - 1 || r_it <= end) && func(list[r_it], list[l_it])) 
					{
						temp[cont] = list[r_it];
						++r_it;
					}//It means they are equal or the indexes are the same we just take the one still in the valid range
					else if (l_it < middle) 
					{
						temp[cont] = list[l_it];
						++l_it;
					}
					else 
					{
						temp[cont] = list[r_it];
						++r_it;
					}
			    }
			 	else 
				{
					if ((r_it > end || l_it < middle) &&  list[l_it] < list[r_it]) 
					{
						temp[cont] = list[l_it];
						++l_it;
					}
					else if ((l_it > middle - 1 || r_it <= end )&& list[r_it] < list[l_it]) 
					{
						temp[cont] = list[r_it];
						++r_it;
					}
					 else if (l_it < middle)
                    {
                        temp[cont] = list[l_it];
                        ++l_it;
                    }
                    else
                    {
                        temp[cont] = list[r_it];
                        ++r_it;
                    }
				}
				++cont;
			}
			// we copy the temp order list in the positions between beginning and end, we are currently considering,  of the original list
			for (int i = beg, j = 0; i <= end; ++j, ++i) 
			{
				list[i] = temp[j];
			}
		}
		catch (const std::bad_alloc& e) 
		{
			std::cout << e.what() << " Fail to allocate, merge sort\n";
			delete[] temp;
			temp = nullptr;
		}
		delete[] temp;
	}
};
}
