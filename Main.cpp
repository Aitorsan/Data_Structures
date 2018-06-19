#include <iostream>
#include "include/vector.h"
#include <utility>
#include<vector>
#include "include/Nodes.h"
#include "include/SingleLinkedList.h"
#include <Windows.h>


int main(){

	asf::vector<int> v{ 3,5,10,1,9,1 };

	std::cout << v << std::endl;
	v.sort_ascendent();
	std::cout << v << std::endl;
	v.sort_descendent();
	std::cout << v << std::endl;
	system("PAUSE");
	return 0;
}



