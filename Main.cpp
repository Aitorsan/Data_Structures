#include <iostream>
#include "include/vector.h"
#include <utility>
#include<vector>
#include "include/Nodes.h"
#include "include/SingleLinkedList.h"



int main(){

	asf::vector<int> v{ 3,5,10,9,1,4,2,6,8,19,17,20,18,7,14,12,15,16,11,13 };

	std::cout << v << std::endl;
	v.sort_ascendent();
	std::cout << v << std::endl;
	v.sort_descendent();
	std::cout << v << std::endl;
	system("PAUSE");
	return 0;
}



