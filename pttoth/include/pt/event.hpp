/** -----------------------------------------------------------------------------
  * FILE:   event.hpp
  * AUTHOR: pttoth
  * EMAIL:  peter.t.toth92@gmail.com
  * PURPOSE:
  *     calls registered functions sequentially with operator()
  * -----------------------------------------------------------------------------
  */

#pragma once

#include <vector>
#include <functional>
#include <stdexcept>

namespace PT{

#define ALLOW_MULTIPLE_INSTANCES 0x1

template<typename... Signature>
class EventBase{
    struct data{
        void*                             target;           //used for identification
        void*                             function_ptr;     //used for identification
        std::function<void(Signature...)> function_obj;     //used during calling       //FUNC_PARAMS

        //ctor
        data():target(nullptr),
            function_ptr(nullptr),
            function_obj(){
        }

        //ctor
        data(void* t,
             void* fptr,
             std::function<void(Signature...)> fobj): target(t),    //FUNC_PARAMS
                                                      function_ptr(fptr),
                                                      function_obj(fobj){
        }

        /**
         * @brief operator ==:
         *   used with object sample during searches
         *      - doesn't check std::function member
         *      - if 'function_ptr' is nullptr, then returns true for every entry with 'target'
         *      - if 'target' is nullptr, then it's a non-class function
         */
        inline bool operator==(const data& other)const{
            if(target == other.target){
                if( (other.function_ptr == nullptr) //if sample only contains listener id, then function_ptr doesn't matter
                    ||(function_ptr == other.function_ptr)){
                    return true;
                }
            }
            return false;
        }

        inline bool is_callable() const{
            return (function_ptr!=nullptr);
        }

        inline void invalidate(){
            target = nullptr;
            function_ptr = nullptr;
            function_obj = nullptr;
        }
    };

    unsigned            _flags;     //CHECK: may not be needed
    size_t              _size;
    size_t              _cap;
    size_t              _index;     //CHECK: queue may be fragmented, so that index != size  (fix occurences!!!!)
    EventBase::data*    _functions;

    /** @brief: returns the index of the element passed,
     *            or -1 if not contained
     */
    inline int index_of(const EventBase::data& d) const{
        for(int i=0; i<_index; ++i){
            if(_functions[i] == d){
                return i;
            }
        }
        return -1;
    }

    inline void defragment_from( EventBase::data* from, int const from_cap){
        int i = 0;
        int j = 0;
        while( (i<from_cap) && (j<_cap) ){
            if( from[i].is_callable() ){
                _functions[j] = from[i];
                ++j;
            }
            ++i;
        }
        _index = j;
    }

    //common mechanics of adding elements
    inline void add_element(EventBase::data d){
        if(nullptr == _functions){
            reserve(1);
        }

        if( -1 == index_of( d ) ){
            if( _index >= _cap ){ //reached end
                if( _size <= _cap/2 ){ //fragmented enough
                    optimize();
                }else{
                    reserve( 2 * _cap );
                }
            }
            _functions[_index] = d;
            ++_index; //CHECK: optimize and reserve fixed index???
            ++_size;
        }
        //TODO: add support multiple registrations
    }

    //common mechanics of removing elements
    inline void remove_element(EventBase::data d){
        int index = index_of(d);
        if( -1 != index ){
            _functions[index].invalidate();
            --_size;
        }
        //TODO: add support for removing multiple occurences
    }

public:
    EventBase(): _flags(0), _size(0),
                 _cap(0), _index(0),
                 _functions(nullptr){
    }

    EventBase(const EventBase& other): _flags(other._flags),
                                        _size(other._size),
                                        _cap(other._cap),
                                        _index(other._index){
        _functions = new EventBase::data[_cap];
        for(int i=0; i<_cap; ++i){
            _functions[i] = other._functions[i];
        }
    }
    EventBase(EventBase&& source): _flags(source._flags),
                            _size(source._size),
                            _cap(source._cap),
                            _index(source._index){
        delete[] _functions;
        _functions = source._functions;
        source._functions = nullptr;
    }

    virtual ~EventBase(){
        delete[] _functions;
    }

    EventBase& operator=(const EventBase& other){
        delete[] _functions;
        _flags = other._flags;
        _size = other._size;
        _cap = other._cap;
        _index = other._index;
        _functions = new EventBase::data[_cap];
        for(int i=0; i<_cap; ++i){
            _functions[i] = other._functions[i];
        }
    }
    EventBase& operator=(EventBase&& source){
        delete[] _functions;
        _flags = source._flags;
        _size = source._size;
        _cap = source._cap;
        _index = source._index;
        _functions = source._functions;
        source._functions = nullptr;
    }
    bool operator==(const EventBase& other)const = delete;

    /**
     * @brief Registers the class member function received in the parameters.
     * @param instance: pointer to the target object
     * @param func: point to the member function to call on the target object
     * @throws std::invalid_argument
     */
    template<typename T>
    inline void add(T* instance, void (T::*func)(Signature...) ){      //FUNC_PARAMS
        if(nullptr == instance){
            throw std::invalid_argument("attempted to register nullptr as listener");
        }else if(nullptr == func){
            throw std::invalid_argument("attempted to register nullptr as function");
        }

        auto lambda = [=](Signature... args) {
            (instance->*func)(args...);
        };

        add_element( EventBase::data(reinterpret_cast<void*>(instance), reinterpret_cast<void*>(func), lambda) ); //FUNC_PARAMS
    }

    /**
     * @brief Registers the global function received in the parameters.
     * @param func: function to call on the target object
     * @throws std::invalid_argument
     */
    inline void add( void (*func)(Signature...) ){          //FUNC_PARAMS
        if( nullptr == func ){
            throw std::invalid_argument("attempted to register nullptr as function");
        }
        add_element( EventBase::data(nullptr, reinterpret_cast<void*>(func), func) );
    }

    /**
     * @brief Removes the member function defined in the parameters
     * @param instance: reference to the target object
     * @param func: member function to call on the target object
     * @throws std::invalid_argument
     */
    template<typename T>
    inline void remove(T* instance, void (T::*func)(Signature...) ){      //FUNC_PARAMS
        if( nullptr == instance ){
            throw std::invalid_argument("attempted to unregister nullptr as listener");
        }else if( nullptr == func ){
            throw std::invalid_argument("attempted to unregister nullptr as function");
        }
        remove_element( EventBase::data(reinterpret_cast<void*>(instance), reinterpret_cast<void*>(func), nullptr) );
    }

    /**
     * @brief Removes the global function defined in the parameters
     * @param func: function to remove from the array
     * @throws std::invalid_argument
     */
    inline void remove(void (*func)(Signature...) ){                //FUNC_PARAMS
        if( nullptr == func ){
            throw std::invalid_argument("attempted to unregister nullptr as function");
        }
        remove_element( EventBase::data(nullptr, reinterpret_cast<void*>(func), nullptr) );
    }

    /**
     * @brief Removes all function registrations regarding the object received as parameter
     *   Note: this will remove any parent's member functions as well,
     *   which the caller may not know about
     * @param object: listener, whose every registered funcion should be removed
     * @throws std::invalid_argument
     */
    inline void remove_object(void* const object){
        if( nullptr == object ){
            throw std::invalid_argument("attempted to unregister nullptr as listener");
        }

        EventBase::data d( reinterpret_cast<void*>(object), nullptr, nullptr);

        //loop until cannot find any more entries with 'target'
        int index = 0;
        while( -1 < index ){
            index = index_of(d);
            if( -1 != index ){
                _functions[index].invalidate();
                --_size;
            }
        }
    }

    /**
     * @brief ensures, that 'size' amount of entries are allocated in memory for the queue
     * @param new_size: the amount of entries we want to be allocated
     */
    inline void reserve(const size_t new_size){
        if(_cap < new_size){
            EventBase::data* old = _functions;
            _functions = new EventBase::data[new_size];
            if(old){
                defragment_from(old, _index);
            }
            _cap = new_size;
            delete[] old;
        }
    }

    /**
     * @brief Rearranges storage by clumping together still active entries in memory
     */
    inline void optimize(){
        //TODO: don't free up memory if empty, this should only be defragmentation
        if(0 == _size){
            delete[] _functions;
            _cap = 0;
            _index = 0;
            _functions = nullptr;
        }else if(_size < _index ){
            defragment_from(_functions, _index);
        }
    }

    /**
     * @brief Dumps unnecessary allocated memory
     */
    inline void shrink_to_fit(){
        if(0 == _size){
            delete[] _functions;
            _cap = 0;
            _index = 0;
            _functions = nullptr;
        }else{
            if(_size < _index){
                EventBase::data* old = _functions;
                _functions= new EventBase::data[_size];
                defragment_from(old, _index);
                _cap = _size;
                delete[] old;
            }
        }
    }

    /**
     * @brief Fires the event, sequentally executing all
     *          registered functions in the order of registration.
     */
    inline void operator()(Signature...args){        //FUNC_PARAMS
        if(_functions){
            for( size_t i=0; i<_index; ++i ){
                if( _functions[i].is_callable() ){
                    _functions[i].function_obj(args...);    //FUNC_PARAMS
                }
            }
        }
    }

}; //end of 'EventBase'



/** @class Event:
 *  @brief Wrapper class that hides the 'operator()' of the actual event object
 *          Its purpose is to prevent external code to trigger the event with the exposed operator().
 */
template<typename... Signature>
class Event{
    EventBase<Signature...>& ev_base;
public:
    Event(EventBase<Signature...>& eventbase):
        ev_base(eventbase){
    }
    Event(const Event& other)                   = delete;       //Note: is there a way to be able to copy correctly?
    Event(Event&& source)                       = delete;
    virtual ~Event(){}
    Event& operator=(const Event& other)        = delete;
    Event& operator=(Event&& source)            = delete;

    bool operator==(const Event& other) const   = delete;

    template<typename T>
    inline void add(T* instance, void (T::*func)(Signature...) ){
        ev_base.add(instance, func);
    }

    inline void add( void (*func)(Signature...) ){
        ev_base.add(func);
    }

    template<typename T>
    inline void remove(T* instance, void (T::*func)(Signature...) ){
        ev_base.remove(instance, func);
    }

    inline void remove(void (*func)(Signature...) ){
        ev_base.remove(func);
    }

    inline void remove_object(void* const object){
        ev_base.remove_object(object);
    }

    inline void reserve(const size_t new_size){
        ev_base.reserve(new_size);
    }

    inline void optimize(){
        ev_base.optimize();
    }

    inline void shrink_to_fit(){
        ev_base.shrink_to_fit();
    }
}; //end of 'Event'



} //end of namespace PT
