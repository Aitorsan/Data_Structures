#include <iostream>
#include "include/vector.h"
#include <utility>
#include<vector>
#include "include/Nodes.h"
#include "include/SingleLinkedList.h"


<<<<<<< HEAD
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
    
=======

int main(){
	int array[4]{ 1,2,3,4 };
	asf::vector<int> v{ 3,5,10,9,1,4,2,6,8,19,17,20,18,7,14,12,15,16,11,13 };
	asf::Sorter<int>::merge_sort(array, 0, 2,nullptr);
	std::cout << v << std::endl;
	v.sort_ascendent();
	std::cout << v << std::endl;
	v.sort_descendent();
	std::cout << v << std::endl;
	system("PAUSE");
>>>>>>> 5a18ed914dd0a44bdb0fa6b5e4a9b402ca9d84fd
	return 0;
}



