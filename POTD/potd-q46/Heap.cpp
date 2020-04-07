#include "Heap.h"
#include <iostream>

void Heap::_percolateDown(int hole) {
    if (hole * 2 >= _data.size()) {return;}

    int i = hole * 2;
    int max;
    if (i + 1 != _data.size()) {
        if (_data[i] > _data[i + 1]) {max = i;}
        else {max = i + 1;}
    }
    else {max = hole * 2;}

    if (_data[hole] < _data[max]) {
        std::swap(_data[hole], _data[max]);
        _percolateDown(max);
    }
}

int Heap::size() const {
    return _data.size();
}

void Heap::enQueue(const int &x){
    _data.push_back(x);
    int hole = _data.size() - 1;
    for(; hole > 1 && x > _data[hole/2]; hole /= 2){
        _data[hole] = _data[hole/2];
    }
    _data[hole] = x;
}

int Heap::deQueue(){
    int minItem = _data[1];
    _data[1] = _data[_data.size() - 1];
    _data.pop_back();
    _percolateDown(1);
    return minItem;
}

void Heap::printQueue(){
    std::cout << "Current Priority Queue is: ";
    for(auto i = _data.begin() + 1; i != _data.end(); ++i){
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

std::vector<int> & Heap::getData() {
    return _data;
}
