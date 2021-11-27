
#include <vector>
#include <iostream>
#include <sstream>
#include <vector>

#pragma once

template <typename T>
class Queue {
private:
    std::vector<T> _data;
    size_t _head, _tail;
    static T _sentinel;

public:
    static const int MAX_DISP_ELEMS = 100;
    
    Queue(size_t size);
    
    static void set_sentinel(const T& elem) { _sentinel = elem; }
    static T get_sentinel() { return _sentinel; }

    bool is_empty() const{
        return _head == _tail;
    };
    
    size_t size() const{
        return (_tail-_head+_data.size())%_data.size();
    }
    
    void resize(size_t size){
        std::vector<T> _keepData;
        size_t theSize = this -> size();
        _keepData.resize(_data.size());
        int i = 0;
        for (i=0; i < (int)_data.size(); i++) {
            _keepData[i] = _data[(_head+i)%_data.size()];
        }
        _tail = theSize;
        _head = 0;
        _data = _keepData;
        _data.resize(size+1);
        if(theSize>size){
            _tail = size;
        }
    }

    const T& peek() const{
        if(is_empty()){
            return _sentinel;
        }
        return _data[_head];
    }
    
    bool dequeue(){
        if(is_empty()){
            return false;
        }
        _head = (_head+1)%_data.size();
        return true;
    }
    
    bool enqueue(const T& elem){
        if(size()==_data.size()-1){
            return false;
        }
        _data[_tail]=elem;
        _tail=(_tail+1)%_data.size();
        return true;
    }

    std::string to_string(size_t limit = MAX_DISP_ELEMS) const{
        std::string keepString = "# Queue - size = " + std::to_string(size()) + "\n" + "data :";
        for (int i = (int)_head, j = 0; i != (int)_tail && j <limit; i=(i+1)%(int)_data.size(), j++) {
            keepString += " " + _data[i];
        }
        if (size() > limit) {
            keepString += " ...";
        }
        keepString += "\n";
        return keepString;
    }

    friend class Tests; // Don't remove this line
};
template <typename T> T Queue<T>::_sentinel = T();

template <typename T> void popalot (Queue<T>& q){
    q.resize(0);
}

template <typename T>
Queue<T>::Queue(size_t size) {
    _data.clear();
    _data.resize(size+1);
    _head = 0;
    _tail = 0;
}

#ifndef Queue_h
#define Queue_h


#endif /* Queue_h */
