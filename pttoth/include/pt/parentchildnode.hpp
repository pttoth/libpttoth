/** -----------------------------------------------------------------------------
  * FILE:    parentchildnode.hpp
  * AUTHOR:  pttoth
  * EMAIL:   peter.t.toth92@gmail.com
  * PURPOSE: Implements methods required to form a hierarchy of nodes.
  *          Classes that inherit it should set its template parameter
  *          to their predeclared class name.
  * -----------------------------------------------------------------------------
  */

#pragma once

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <assert.h>

namespace PT{

template<class T>
class ParentChildNode{

    ParentChildNode*                mParent;
    std::vector<ParentChildNode*>   mChildren;
    uint32_t                        mChildCount;

public:
    ParentChildNode():
            mParent(nullptr){
    }
    virtual ~ParentChildNode(){
    }

    //copy
    ParentChildNode(const ParentChildNode& other)                       = delete;
    ParentChildNode&    operator=(const ParentChildNode& other) const   = delete;

    //move
    ParentChildNode(ParentChildNode&& source)                           = delete;
    ParentChildNode&    operator=(ParentChildNode&& source)             = delete;

    bool                operator==(const ParentChildNode& other) const  = delete;

    ParentChildNode* getParent(){
        return mParent;
    }

    std::vector<ParentChildNode*> getChildren(){
        std::vector<ParentChildNode*> retval;
        retval.reserve(mChildCount);
        for(ParentChildNode* current : mChildren){
            if(current != nullptr){
                retval.push_back(current);
            }
        }
        return retval;
    }

    //throws std::logic_error(hierarchy wouldn't stay acyclic)
    virtual void setParent(ParentChildNode* parent){
        if(mParent != nullptr){
            mParent->removeChild(this);
        }
        mParent = parent;
        if(mParent != nullptr){
            mParent->addChild(this);
        }
    }

protected:
    //throws std::invalid_argument (child already present)
    virtual void addChild(T* child){
        if( -1 < getChildIndex(child) ){
            throw std::invalid_argument("Tried to add child that is already contained");
        }else{
            _defragmentParentChildNodeChildren();
            mChildren.push_back(child); //TODO: use smarter defragmentation
            --mChildCount;
            assert(-1 < mChildCount);
        }
    }

    //throws std::invalid_argument (child not found)
    virtual void removeChild(T* child){
        int idx = getChildIndex(child);
        if( idx < 0){
            throw std::invalid_argument("Tried to remove child that is not contained");
        }else{
            mChildren[idx] = nullptr;
            ++mChildCount;
            assert(-1 < mChildCount);
        }
    }
private:
    virtual int getChildIndex(ParentChildNode* child){
        for(size_t i=0; i<mChildren.size(); ++i){
            if(mChildren[i] == child){
                return static_cast<int>(i);
            }
        }
        return -1;
    }
    void _defragmentParentChildNodeChildren(){
        size_t w=0,r=0;
        for(r=0; r<mChildren.size(); ++r){
            if(mChildren[r] != nullptr){
                mChildren[w] = mChildren[r];
                if(w < r){
                    mChildren[r] = nullptr;
                }
                ++w;
            }
        }
    }
};

} //end of namespace pt


