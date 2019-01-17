#pragma once

#include <cstddef>
#include <vector>
#include <string>

namespace pttoth{

template<typename T>
inline int indexOfInVector(std::vector<T>& vec, T& element){
    for(int i=0; i<vec.size(); ++i){
        if(vec[i] == element){
            return i;
        }
    }
    return -1;
}

template<typename T>
inline bool containedInVector(std::vector<T>& vec, T& element){
    return ( -1 < indexOfInVector(vec, element) );
}

template<typename T>
inline void removeElementInVector(std::vector<T>& vec, size_t pos){
    auto iter = vec.begin()+pos;
    vec.erase(iter);
}

inline std::string
trimWhitespaces(const std::string& str){
    if( 0 < str.length() ){
        size_t low = 0;
        size_t high = str.length()-1;
        bool done = false;
        while(!done){
            if( low < str.length()
              && isspace(str[low]) ){   ++low;
            }else{                      done = true;
            }
        }
        done = false;
        while(!done){
            if( low <= high
              && isspace(str[high]) ){  --high;
            }else{                      done = true;
            }
        }
        if(low <= high){
            return str.substr(low, high-low+1);
        }
    }
    return std::string();
}

inline bool
splitString(std::string* retval, const std::string& str){
    size_t idx = str.find("=");
    if(std::string::npos != idx){
        retval[0] = str.substr(0, idx);
        retval[1] = str.substr(idx+1, str.length()-idx-1);
        return true;
    }
    return false;
}

} //end of namespace

