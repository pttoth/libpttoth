#pragma once

#include "pttoth/tuple.hpp"

#include <string>
#include <iostream>

namespace pttoth{

class test_tuple{

public:
    test_tuple(){}
    bool run();

    //doesn't compile, have to define template in the return type
    /*
    Tuple2 t2test(){
        int i = 5;
        std::string str("this is a string");
        return Tuple2(i, str);
    }
    */

    Tuple2<int, std::string> t2test(){
        int i = 5;
        std::string str("this is a string");
        return Tuple2<int, std::string>(i, str);
    }

};

bool test_tuple::
        run(){
    //Tuple2 res2 = t2test(); // this should be able to deduce templates but doesn't
    auto res2 = t2test();
    std::cout << res2._1 << "," << res2._2 << "\n";
}

} //namespace pttoth
