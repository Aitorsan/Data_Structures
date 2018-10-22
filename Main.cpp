#include <iostream>
#include "include/vector.h"
#include <utility>
#include<vector>
#include "include/Nodes.h"
#include "include/SingleLinkedList.h"


#include<iostream>



int main(){

    asf::SingleLinkedList<int> list1;
    asf::SingleLinkedList<int>list2;
    
    list1.insert(3);
    list1.insert(2);
    list1.insert(5);
    list1.insert(7);
    std::cout << "\n*********************************\n";
    std::cout <<  " Copy assignament";
    std::cout << "\n*********************************\n";
   std::cout << "\n-------------\nBefore copy assignament\n------------\n";
    std::cout << "List 1: \n";
    list1.print_elements();
    std::cout << "List 2: \n";
    list2.print_elements();
    std::cout << "\n-------------\nlist2 = list1;\n------------\n";
    list2 = list1;
    std::cout << "\n-------------\nAfter copy assignament\n------------\n";
    std::cout << "List 1: \n";
    list1.print_elements();
    std::cout << "List 2: \n";
    list2.print_elements();
    
    std::cout << "\n*********************************\n";
    std::cout <<  " move assignament";
     std::cout << "\n*********************************\n";
    std::cout << "\n-------------\nlist2 = std::move(list1);\n------------\n";
    list2 = std::move(list1);
    
    std::cout << "\n-------------\nAfter move assignament\n------------\n";
    std::cout << "List 1: \n";
    list1.print_elements();
    std::cout << "List 2: \n";
    list2.print_elements();
    std::cout << "\n*********************************\n";
    std::cout <<  " reverse list2";
    std::cout << "\n*********************************\n";
    list2.reverse_list();
    list2.print_elements();
    
	return 0;
}



