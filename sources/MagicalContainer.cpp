#include "MagicalContainer.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace ariel;
using namespace std;

MagicalContainer::MagicalContainer():_container(),_size(0){}        //Default constructor.
MagicalContainer::~MagicalContainer(){                              //Destructor
            _prm_cont.clear();
        }
void MagicalContainer::addElement(int num) {
    _container.push_back(num);
    _size++;
    sort(_container.begin(),_container.end());      //sort the element in ascending order.

        _prm_cont.clear();                      //Rearrange the prime pointers.
        for(auto itr = _container.begin() ; itr!=_container.end();++itr){
            if(isPrime(*itr)){
                int *sol = &(*itr);
                _prm_cont.push_back(sol);
            }
        }
}

void MagicalContainer::removeElement(int num) {
    bool exist = false;    
    for (auto it = _container.begin(); it != _container.end(); ++it) {
        if (*it == num) {
            _container.erase(it);
            _size--;
            exist = true;
            break;
        }
    }
    if(!exist)
    throw runtime_error("couldn't remove non exisiting element!");
}

//AscendingIterator Constructors
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) : _container(other._container), _current_index(other._current_index) {}
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : _container(container), _current_index(0) {}
void MagicalContainer::AscendingIterator:: setIndex(int idx){
    if(idx>this->_container.size()) {throw std::invalid_argument("Index not in range.");}
    this->_current_index = idx;
}
//SideCrossIterator Constructors
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) : _container(other._container), _current_index(other._current_index),counter(other.counter) {}
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : _container(container), _current_index(0),counter(0) {}
void MagicalContainer::SideCrossIterator:: setIndex(int idx){
    if(idx>this->_container.size()) {throw std::invalid_argument("Index not in range.");}
    this->_current_index = idx;
}
//PrimeIterator Constructors
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) : _container(other._container), _current_index(other._current_index) {}
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : _container(container), _current_index(0) {}
void MagicalContainer::PrimeIterator:: setIndex(int idx){
    if(idx>this->_container.size()) {throw std::invalid_argument("Index not in range.");}
    this->_current_index = idx;
}
//support method
bool ariel::isPrime(int num){       
    if(num<2) return false;
    if(num == 2||num==3) return true;
    for(int i=2;i<=sqrt(num);++i){
        if(num%i==0) return false;
    }
    return true;
}
