#include <iostream>
#include "include/vector.h"
#include <utility>
#include<vector>
#include "include/Nodes.h"
#include "include/SingleLinkedList.h"


#include<iostream>



class parent{
    
public:
    
    virtual void method()= 0;
    virtual void mehthod_two() = 0;
    
    
};



class child:public parent{
    
    
    public :
    
    void method(){
        std::cout << "child one"<<std::endl;
    }
    
    void method_two(){
        std::cout << "mehtod two child one" << std::endl;
        
    }
    
    
};


class subchild:public parent{
    virtual void method(){
    std::cout << "is private you cant use it" << std::endl;}
    virtual void mehthod_two(){
    std::cout << "method two is private you cant use it" <<std::endl;
    }
    public :
    
    void nowyes(){
       mehthod_two();
        method();
    }
    
    
};

int main(){

    
    subchild c;
    c.nowyes();

 
	return 0;
}



