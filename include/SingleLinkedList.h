#pragma once
// MSC standards compliance issues
#ifdef _MSC_VER
#include "bw_msposix.h"
#else
#define _NOEXCEPT noexcept
#endif
#include <utility>
#include "Nodes.h"

namespace asf
{
	template<typename T>
	class SingleLinkedList
    {  
       Node<T>*m_head, *m_curr, *m_prev, *m_rear;
       unsigned int m_size;
       unsigned int curr_position;
	public:
		SingleLinkedList();
		SingleLinkedList(const SingleLinkedList<T>&);
		SingleLinkedList(SingleLinkedList<T>&&)_NOEXCEPT;
		~SingleLinkedList();
		//checks if the current pointer (m_curr) has reached the end of the list
		bool end_of_list() { return m_curr == m_rear; }
		// advances the current pointer position
		void advance_position();
		// Insert at the front of the list
		void insert_before(const T& element);
		// Insert at the front of the list
		void insert_after(const T& element);
		//Insert an element at the end of the list 
		void insert_at_rear(const T& element);
		// Insert an element at the current position of the m_curr pointer is pointing to
		void insert(const T& element);
		// remove the desire element from the list if is in the list
		void remove(T element);
		//check if the list is empty
		bool is_empty()const { return m_size == 0; }
		// reverse the list the first node is the last and the last is the first.
		void reverse_list();
        //size of the list number of elements
		int size()const;
        //print elements inside the list
        void print_elements();
		//operator overloading
		SingleLinkedList<T>& operator= ( SingleLinkedList<T>);
		//SingleLinkedList<T>& operator= (SingleLinkedList<T>&&);
		template<typename E>
		SingleLinkedList<T>& operator = (SingleLinkedList<E>);

	private:
		//private methods to help
        Node<T>* remove(Node<T>* node,  const T& element);
		Node<T>* get_node(const T& element, Node<T>* next = nullptr)const;
        void reverse_list(Node<T>* node);
        void swap(SingleLinkedList<T>& other);
        void reset_state();

	};



	/***************************
	*Constructors
	***************************/
	template<class T>
	SingleLinkedList<T>::SingleLinkedList()
		:m_head(nullptr),
		m_curr{ nullptr },
		m_prev{ nullptr },
		m_rear{ nullptr },
		m_size{},
		curr_position{} {
		//nothing else to do
	}

	//copy constructor
	template<class T>
	SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T>& list) :
		m_head(nullptr),
		m_curr{ nullptr },
		m_prev{ nullptr },
		m_rear{ nullptr },
		m_size{},
		curr_position{}
    {

		if (!list.is_empty())
        {

			Node<T>* iterator = nullptr;
			iterator = list.m_head;
			try
            {
				m_head = new Node<T>(list.m_head->get_data(), nullptr);
				m_curr = m_head;
				m_rear = m_head;
				m_prev = m_head;
				//int counter = 0;
				while (iterator->get_next() )
                {
					iterator= iterator->get_next();
					m_rear->set_next( new Node<T>(iterator->get_data(), nullptr));
					m_rear = m_rear->get_next();
				
					//for debugging and testing
//                    ++counter;
//                    if (counter == 10) {
//                        throw new std::bad_alloc();
//                      }
				}
				iterator = nullptr;
			}
			catch (const std::bad_alloc& e)
            {
				//because our nodes know how to clean up themselves
				// if allocation fails in one of the iterations we delete the head 
				// and all the allocated nodes will be also deleted
				m_head = nullptr;
				m_curr = nullptr;
				m_rear = nullptr;
				delete m_head;
			}
		}
	}

	//Move constructor
	template<typename T>
<<<<<<< HEAD
    inline SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T>&& other) _NOEXCEPT
	{
        m_head = other.m_head;
        m_prev = other.m_prev;
        m_curr = other.m_curr;
        m_rear = other.m_rear;
        m_size = other.m_size;
        curr_position= other.curr_position;
        other.reset_state();
=======
	inline SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T>&& rhs)
	{
		//We point to the list we are moving
		this->m_head = rhs->m_head;
		this->m_prev = rhs->m_prev;
		this->m_curr = rhs->m_curr;
		this->m_rear = rhs->m_rear;
		this->m_size = rhs->m_size;
		this->curr_position = rhs->curr_position;

		//finally we reset the variables to cero from rhs and make the pointers nullptr
		rhs->m_head = nullptr;
		rhs->m_prev = nullptr;
		rhs->m_curr = nullptr;
		rhs->m_rear = nullptr;
		rhs->m_size = 0;
		rhs->curr_position = 0;

>>>>>>> 5a18ed914dd0a44bdb0fa6b5e4a9b402ca9d84fd
	}


	//clean up, first we unlink all pointers in the list except the head pointer.
	//Then we delete head pointer, and the destructors of the nodes will clean up
	// them own next pointers, making a deletion chaining.
	template<typename T>
	inline SingleLinkedList<T>::~SingleLinkedList()
	{
		m_prev = nullptr;
		m_curr = nullptr;
		m_rear = nullptr;
		delete m_head;
		m_head = nullptr;
		
	}

	//advance the current position
	template <typename T>
	inline void SingleLinkedList<T>::advance_position() {
		if (!end_of_list()) {
			m_prev = m_curr;
			m_curr = m_curr->m_next;
		}
		else {
            std::cout << "It is not posible to advance more through the list" << std::endl;
		}

	}

	//insert before the current pointer position
	template<typename T>
	inline void SingleLinkedList<T>::insert_before(const T & element)
	{
		if (m_prev == nullptr) {
			insert(element);
		}
		else {
			m_prev->m_next = getNode(element, m_curr);
			m_prev = m_prev->m_next;
			++m_size;
		}


	}
	//Insert an element after the current position
	template<typename T>
	inline void SingleLinkedList<T>::insert_after(const T & element)
	{
		if (m_curr == m_rear)
        {
			insert_at_rear(element);
		}
		else
        {
			m_curr->set_next ( get_node(element, m_curr->get_next()));
			++m_size;
		}

	}


	//Insert an element at the end of the list
	template<typename T>
	inline void SingleLinkedList<T>::insert_at_rear(const T & element)
	{
		if (m_head == nullptr) {
			insert(element);
		}
		else {
			m_rear->set_next( get_node(element));
            m_rear = m_rear->get_next();
			++m_size;
		}
	}


	//Insert a node where current position is
	template<typename T>
	inline void SingleLinkedList<T>::insert(const T & element)
	{
		Node<T>* new_node = nullptr; 
		if (m_prev == nullptr) {

			 new_node = get_node(element, m_head);
			 m_head = new_node;
			
		}
		else {
			new_node = get_node(element);
			insert_after(element);

		}
		// if m_prev is equal to rear that means this is the first element
		// we are inserting in a empty list. Cause both will be pointing to nullptr.
		// In that case the first element is also the last so we have to update rear
		// to point to the last element.
		if (m_prev == m_rear) {
			m_rear = new_node;
		}
		//common operation
		m_curr = new_node;
		++m_size;

	}

    /**
     * Remove an element from the list, if the list is not empty
     */
	template<typename T>
	inline void SingleLinkedList<T>::remove(T element)
	{
        if(!is_empty())
        {
           m_head = remove(m_head,element);
        }
        else
        {
           std::cout << "The list is empty\n";
        }
	}
    
    
    /*************************************************************
     * Remove recursively a node containing the element to delete
     *************************************************************/
    template<typename T>
    Node<T>* SingleLinkedList<T>::remove(Node<T>* node, const T& element){
        
        if(node != nullptr)
        {
            if( node->get_data() == element)
            {
                Node<T>* temp = node->get_next();
                node->set_next(nullptr);
                delete node;
                node= nullptr;
                --m_size;
                return temp;
            }
            else
            {
               node->set_next(remove(node->get_next(), element));
               return node;
            }
        }
        return nullptr;
    }
    
	template<typename T>
	inline void SingleLinkedList<T>::reverse_list()
    {
        if(m_head != nullptr)
        {
            m_rear = m_head;
            reverse_list(m_head);
            m_rear->set_next(nullptr);
        }
    }
    
    template<typename T>
    inline void SingleLinkedList<T>::reverse_list(Node<T>* node)
    {
         if(node->get_next() == nullptr)
         {
            m_curr =  m_head = node;
         
         }
         else
         {
             reverse_list(node->get_next());
             m_curr->set_next(node);
             m_curr = node;
         }
        
    
    }


	//return the number of elements in the list. The size
	template<typename T>
	inline int SingleLinkedList<T>::size() const
	{
		return m_size;
	}

   //print all the elements contained in the list
    template<typename T>
    void SingleLinkedList<T>::print_elements(){
        
        Node<T>* iterator=m_head;
        while(iterator != nullptr){
            std::cout << "["<<iterator->get_data() <<"]->";
            iterator=iterator->get_next();
        }
        std::cout << std::endl;
        iterator=nullptr;
    }
    
    
	//conversion between two different but compatible types of list like list of floats and ints.
	template<typename T>
	template<typename E>
	inline SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList<E>rhs)
	{
		// TODO: insert return statement here
	}


	//move assignament operator
	template<typename T>
	inline SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList<T> other)
	{
        swap(other);
        return *this;
	}
    
    template<typename T>
    inline void SingleLinkedList<T>::swap(SingleLinkedList<T>& other)
    {
        std::swap(m_head,other.m_head);
        std::swap(m_curr,other.m_curr);
        std::swap(m_prev,other.m_prev);
        std::swap(m_rear,other.m_rear);
        std::swap(m_size,other.m_size);
        std::swap(curr_position,other.curr_position);
        
    }

    template<typename T>
    inline void SingleLinkedList<T>::reset_state()
    {
        m_head = m_curr = m_prev = m_rear = nullptr;
        m_size = 0;
        curr_position = 0;
    }
	/*********************
	 * Private mehtods
	 *********************/
	//creates a node
	template<typename T>
	inline Node<T>* SingleLinkedList<T>::get_node(const T & element,Node<T>* next ) const
	{
		Node<T>* new_node = nullptr;
		try{
			new_node = new Node<T>{ element,next };
		}
		catch (std::bad_alloc& excp) {
			delete new_node;
			new_node = nullptr;
			std::cerr << "allocation has failed:\nfile:SingleLinkedList.h line(210)\nreturn: nullptr\n" << std::endl;
		}

		return new_node;
	}

}// end of asf namespace

