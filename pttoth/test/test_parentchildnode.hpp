#pragma once

#include "pt/parentchildnode.hpp"

#include <string>
#include <iostream>

namespace PT{

class ParentChildNodeTest{


    class TestClass1: public ParentChildNode<TestClass1>{
        std::string mName;

        TestClass1(std::string name): mName(name){
        }
    public:
        std::string getName()const{ return mName; }

        void write(){
            std::cout << mName << "\n";
            std::cout << "  parent: " << getParent()->get << "\n";
        }
    };



public:
    void run(){
        TestClass1 class1;


    }


};

}
