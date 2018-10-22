#pragma once
/*
// This is a naive implementation of the vector data structures.
// This projec is only for educational purppose.
// Do not use this class in a serous projects.
//TODO:Allocator important thing to improve
// autor: Aitor sanmartin ferreira
*/
#include<initializer_list>
#include <stdexcept>
#include "algorithms.h"
#include <ostream>
#define DEFAULT_CAPACITY 4
#define INC_CAPACITY_FACTOR 2
namespace asf
{
	template <typename T>
	class vector
    {
		// that is the number of elements that the array contains, even thoug the capacity is the real size it is forbbiden to write beyond the bounds of the size
		int m_size;
		//capacity of the array the real size, for performance reasons it is better to have extra space cause reallocating is expensive
		int m_capacity;
		//the container where the elements are store
		T* m_container; 
		//points to the last free space in the array
		T*  end_pointer ;
	public:
		vector();
		vector(const std::initializer_list<T>& l);
		vector(const asf::vector<T>& rhs);
		vector(asf::vector<T>&& rhs);
		~vector();

		//methods
		int  size()const { return m_size; };
		int capacity()const { return m_capacity; }
		void resize(int new_capacity);
		void shrink();
		void clean();
		void push_back(T element);
		void sort_custom(bool(*ptr)(const T& a, const T& b));
<<<<<<< HEAD
		void sort();
=======
		void sort_descendent();
		void sort_ascendent();

>>>>>>> 5a18ed914dd0a44bdb0fa6b5e4a9b402ca9d84fd
		//overloaded operators	
		T&  operator [](int index);
		// pointer cast operator
		operator T*()const;
		// assignament operator
		vector<T>& operator=(const vector<T>& rhs)const;
		//assignament operator for diferent types but compatible
		template<typename E>
		vector<T>& operator= (const vector<E>& rhs)const;
		//move assignament operator
		vector<T>& operator= (vector<T>&& rhs);
		//friend overload ostream object
		template<typename E>
		friend std::ostream& operator<<(std::ostream& out, const vector<E>& rhs);
	};
	//******************************
	// Implementation of the class
	//******************************

	//******************************
	// Constructors
	//******************************

	//No parameter constructor
	template <typename T>
	vector<T>::vector() :m_size(0), m_capacity(DEFAULT_CAPACITY), m_container(new T[DEFAULT_CAPACITY]),end_pointer(m_container){}


	//Initializer list constructor
    template <typename T>
	vector<T>::vector(const std::initializer_list<T>& l)
          : m_size(l.size())
          , m_capacity(m_size*INC_CAPACITY_FACTOR)
          , m_container(new T[m_capacity])
          , end_pointer(nullptr)
    {
			int index = 0;
			for (typename std::initializer_list<T>::iterator it = l.begin(); it != l.end(); ++it) {
				*(m_container + index) = *it;
				++index;
			}
        //This work because we are doubling the size of the vector so even thoug we have less elements
        //in the array, its valid to point to the next empty space. In that way we can push_back a new
			end_pointer = &m_container[m_size];
	}

	//Copy constructor
	template <typename T>
	vector<T>::vector(const vector<T>& rhs)
        : m_size{rhs.m_size }
        , m_capacity{ rhs.m_capacity }
        , m_container {new T[m_capacity] }
        , end_pointer{ nullptr }
    {
        for (int i = 0; i < m_size; ++i)
        {
        //because we overload the sucscript operator we can simply do rhs[i] instead rhs.m_container[i]
           m_container[i] = rhs[i];
        }
        //after copying all the elements into the new vector we place the end_iterator after the last element
			end_pointer = &m_container[m_size];
	}

	//move constructor
	template<typename T>
	vector<T>::vector( vector<T>&& rhs)
       :m_size(rhs.m_size)
       ,m_capacity(rhs.m_capacity)
       ,m_container(rhs.m_container)
       ,end_pointer(rhs.end_pointer)
    {
		rhs.m_container = nullptr;
		rhs.end_pointer = nullptr;
		rhs.m_size = 0;
		rhs.m_capacity = 0;
	}

   /*************************
	*  Destructor
	************************/
	template <typename T>
	vector<T>::~vector()
    {
		delete[] m_container;
		m_container = nullptr;
	}

	/*************************************
	*    Member methods
	*************************************/
	//Sort an element with a given predicate, that says how to compare the elements
	template<typename T>
	inline void vector<T>::sort_custom(bool(*ptr)(const T &a, const T &b))
	{
<<<<<<< HEAD
       merge_sort<T>(m_container, m_size, ptr);
=======
		 Sorter<T>::merge_sort(m_container, 0,m_size-1, ptr);
	}
	// Sort the vector in ascending order by default. 
	// Should be use with objects that has overloaded 
	// the comparation overloaded operators
	template<typename T>
	inline void vector<T>::sort_descendent() {
		Sorter<T>::merge_sort(m_container,0, m_size-1, [](const T&a, const T&b) {return a > b; });
>>>>>>> 5a18ed914dd0a44bdb0fa6b5e4a9b402ca9d84fd
	}

	// Sort the vector in ascending order by default. 
	// Should be use with objects that has overloaded 
	// the comparation overloaded operators
	template<typename T>
<<<<<<< HEAD
	inline void vector<T>::sort()
    {
		merge_sort<T>(m_container, m_size, [](const T&a, const T&b) {return a < b; });
=======
	inline void vector<T>::sort_ascendent() {
		Sorter<T>::merge_sort(m_container, 0, m_size-1);
>>>>>>> 5a18ed914dd0a44bdb0fa6b5e4a9b402ca9d84fd
	}


	//Delete the content within the vector
	template <typename T>
	inline void vector<T>::clean()
    {
		if(m_container != nullptr)
        {
			delete[] m_container;
			m_container = nullptr;
		}
		m_size = 0;
		m_capacity = 0;
		end_pointer = nullptr;
	}

	//push back method, insert an element at the end of the vector
	template<typename T>
	inline void vector<T>::push_back(T element)
    {
		//if the size its greater than or equal to the capacity we have to reallocate memory to insert the new element
		if ( m_size >= m_capacity)
        {
			// capacity it will be twice the size of the actual array
			m_capacity = m_size * INC_CAPACITY_FACTOR;
			//we create the new array with the new capacity
			T* temp = new T[m_capacity];
			//now we copy all the elements of the older array into the new array with more capacity
			for (int i = 0; i < m_size; ++i)
            {
               temp[i] = m_container[i];
			}
			//now the end pointer will point to the next empty space at the end
			end_pointer = &temp[m_size];
			//we free the memory of the old array
			delete[] m_container;
			// and we make the container of our vector to point to the new array
			m_container = temp;
			//we set temp pointer to nullptr cuase we already transfer the ownership of the array
			temp = nullptr;
		}
		// if the vector is empty, that means we just clean the array or we have transfered the ownership
		else if (m_size == 0)
        {
			// the capacity will be the default
			m_capacity = DEFAULT_CAPACITY;
			// we allocate the array with the default capacity
			m_container = new T[m_capacity];
			//because the array is empty end_pointer has to point to the first free space on the array that for sure is the first index 0
			end_pointer = m_container;
		}
		//now we can insert the new element at the end of the array
		*end_pointer = element;
		//we increment the position of the end pointer by one
		++end_pointer;
		// we increment the size of the array ( the size is the number o elements in the array, and the capacity is the actual reserved memory space of the array)
		++m_size;
	}

	//resize the vector
	template<typename T>
	inline void vector<T>::resize(int new_capacity)
    {
		if (new_capacity <= 0)
        {
			clean();
		}
		else if ( new_capacity <= m_size)
        {
			shrink();
		}
		else
        {
			T* temp = new T[new_capacity];
			m_capacity = new_capacity;

			for (int i = 0; i < m_size; ++i)
            {
               temp[i] = m_container[i];
			}
			end_pointer = nullptr;
			delete[] m_container;
			m_container = temp;
			end_pointer = &m_container[m_size];	
		}
	}

	// we reduce the capacity of the vector and tight up the space in the vector
	// we should use this if we know that we will not put more elements int he array nothing else
	// tODO:allocators will be the way to proceed in this case
	template<typename T>
	inline void vector<T>::shrink()
    {

		if (m_size > 0) {
			m_capacity = m_size + 1;

			T* temp = new T[m_capacity];
			for (int i = 0; i < m_size; ++i) {
				temp[i] = m_container[i];
			}

			delete[]m_container;
			m_container = temp;
			temp = nullptr;
			end_pointer = &m_container[m_size];
		}
	}

	/************************************
	*     Operator overloads
	************************************/
	template<typename T>
	inline T& vector<T>::operator[](int index)
	{    //bound checking
		//if the index is less than 0 or greater than size we throw and exception
		if (index < 0 || index > m_size) {
			throw std::out_of_range("out of range");
		}
	return *(m_container + index);
	}

	//type conversion overload
	template<typename T>
	inline vector<T>::operator T*() const
	{    //return the addres to the first element of the array
		return m_container;
	}

	template<typename T>
	inline vector<T>& vector<T>::operator=(const vector<T>& rhs)const
	{
		//check for self asignament
		if (this == &rhs) {
			return *this;
		}
   
		m_size = rhs.m_size;
		delete[] m_container;
	
		if (m_size > 0) {
			m_container = new T[m_size];
			for (int i = 0; i < m_size; ++i) {
				m_container[i] = rhs.m_container[i];
			}
		}
		else {
			m_container = nullptr;
		}
		return *this;
	}

	//assignament operator for different types
	template <typename T>
	template<typename E>
	vector<T>& vector<T>::operator=(const vector<E>& rhs)const{

		//to be able to make the comparason we need to cast the two vectos to a void pointer
		if ((void*)this == (void*)&rhs) {
			return *this;
		}

		//because we can't acces private members of a vector of other type
		//we need to instantiate a copy of the original
		vector<E> copy(rhs);

		//now we do the same as the other assignament operator
		m_size = copy.size();
		delete[] m_container;
		m_container = new T[m_size];
		for (int i = 0; i < m_size; ++i) {
			m_container[i] = copy[i];
		}
		return *this;
	}
	//move assignament operator
	template<typename T>
	 vector<T>& vector<T>::operator=(vector<T>&& rhs) {
		if (this == &rhs)
			return *this;

		delete[] m_container;
		m_size = rhs.m_size;
		rhs.m_size = 0;
		m_container = rhs.m_container;
		rhs.m_container = nullptr;

		return *this;
	}

	// << overload operator for print to the console
	template <typename E>
	 inline std::ostream& operator<<(std::ostream& out, const vector<E>& rhs) {

			for (int i = 0; i < rhs.m_size; ++i) {
				out << "[" << rhs[i] << "]";
			}
			out << "\n";
			return out;
		}
}//end asf namespace

