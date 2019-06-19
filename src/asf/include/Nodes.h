#pragma once
#include <iostream>
#include <exception>

namespace asf {

	//Interface for nodes
	template<class T>
	class INode {

	public:
		virtual ~INode() {}
		virtual void insert(T&)= 0;
		virtual T get_data()const = 0;
	};

/*
* Class single node. Cannot be copied, moved or assigned. The class node will be not be exposed to the user, and we do not have the intention
* to copy nodes from each other or move them in the node class itself. That management belongs to the data structure that will use the node.
* So we delete assignaments and copy and move constructors.
* 
* If in future implementations, if that purpose change we will provide an aproppiate copy, move constructors and assignament operator 
*/
template <typename T>
class Node:public INode<T> {
	T m_data;
	Node<T>* m_next;
public:
	Node():m_data(T{}),m_next(nullptr) {}
	Node(T data,Node<T>* next = nullptr ) : m_data(data), m_next(next) {}
	Node(const Node<T>& copy)= delete;
	Node(Node<T>&& move) = delete;
	//virtual destructor because of inheritance
	virtual ~Node()override;
	//virtual methods
	virtual void insert(T& element)override;
	virtual T get_data()const override  { return m_data; }
	//non virtual methods
    Node<T>* get_next()const ;
	void set_next(Node<T>* next);
	//overloaded operators
	Node<T>& operator= (const Node<T>& rhs)= delete;
	Node<T>& operator= (Node<T>&& rhs) = delete;
	friend std::ostream& operator<<(std::ostream& out, const Node<T>& rhs);
};

//Destructor
template<typename T>
Node<T>::~Node() {
	delete m_next;
	m_next = nullptr;
}
//TOOD: not sure if it will work properly
//add the element in a new node after itself
template<typename T>
void Node<T>::insert(T& element) {
	
		Node<T>* new_node = new Node<T>(element,m_next);
		m_next = new_node;
}

//If we get the next node is for use it. So we are pedantic and make a warning if you discard it lol
template<typename T>
 [[nodiscard]]inline Node<T>* Node<T>::get_next() const
{    //the data structure will be responsable to check whether the node is nullptr or is pointing to somenthing        
	return m_next;
}

 //Set the next pointer point to a new node. If the node is already pointing to something the function manage the disconction to avoid future problems
template<typename T>
inline void Node<T>::set_next(Node<T>* next)
{
	// unlink the node
	if (m_next != nullptr)
		m_next = nullptr;
	m_next = next;
}


//Operator << overloaded to use std::cout and print the elements out to the console
template <typename T>
 std::ostream& operator<<(std::ostream& out, const Node<T>& rhs) {
	 out << rhs.m_data << " ";
	 return out;
} 



}//end of asf namespace





