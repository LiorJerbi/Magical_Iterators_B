#include "MagicalContainer.hpp"
#include <vector>
#include <iostream>
#include <cmath>

using namespace ariel;
using namespace std;

MagicalContainer::MagicalContainer():_container(),_size(0){}
void MagicalContainer::addElement(int num) {
    _container.emplace_back(num);
    _size++;
    int* ptr = new int(_container.back());
    //ascending container add.
    if(_asc_cont.empty()){      //no pointers in vector
        _asc_cont.emplace_back(ptr);
        auto tst = _asc_cont.begin();        
    }
    else {
        bool inserted = false;
        for (auto itr = _asc_cont.begin(); itr != _asc_cont.end(); ++itr) {
            if (**itr > *ptr) { // number is smaller than the value in place
                if(itr==_asc_cont.begin()){
                    int* tmp = _asc_cont.back();
                    _asc_cont.pop_back();
                    _asc_cont.emplace_back(ptr);
                    _asc_cont.emplace_back(tmp);
                    inserted = true;
                    break;
                }
                else{
                    _asc_cont.emplace(itr, ptr);
                    inserted = true;
                    break;
                }
            }
        }
        if (!inserted) {
            _asc_cont.emplace_back(ptr);
        }
    }


    //sidecross add.
    if(_sicr_cont.empty()){     // no pointers in the vector
        _sicr_cont.emplace_back(ptr);
    }
    else{
        _sicr_cont.clear();

        vector<int*>::const_iterator begin=_asc_cont.cbegin();
        vector<int*>::const_reverse_iterator end=_asc_cont.crbegin();
        int i = _asc_cont.size()/2;
        for(;i<_asc_cont.size() && *begin != *end; ++begin,++end,++i){    //take first and last pointers from ascending vector and push them one after one.(O(n) at max)
            _sicr_cont.emplace_back(*begin);
            _sicr_cont.emplace_back(*end);
        }
        if(_asc_cont.size() > _sicr_cont.size())    //if size is odd we missed the last number need to add it.
            _sicr_cont.emplace_back(*begin);   
    }

    //prime add.
    if(isPrime(num)){
        if(_prm_cont.empty()){      //no pointers in the vector
            _prm_cont.emplace_back(ptr);
        }
        else{
            bool inserted = false;
            for(vector<int*>::const_iterator itr=_prm_cont.cbegin(); itr !=_prm_cont.cend();++itr){   //putting the pointer in the right place.(maximum o(n))
                if(**itr>*ptr){
                    if(itr==_prm_cont.begin()){
                      int* tmp= _prm_cont.back();
                    _prm_cont.pop_back();
                    _prm_cont.emplace_back(ptr);
                    _prm_cont.emplace_back(tmp);
                    inserted=true;
                    break;
                    }
                    _prm_cont.emplace(itr,ptr);
                    inserted =true;
                    break;
                }
            }
            if(!inserted){
                _prm_cont.emplace_back(ptr);
            }
        }
    }
    
}

void MagicalContainer::removeElement(int num) {
    bool exist = false;
    for(auto itr=_asc_cont.begin();itr != _asc_cont.end(); ++itr){
        if(**itr == num){
            _asc_cont.erase(itr);
            break;
        }
    }
    for(auto itr=_sicr_cont.begin();itr != _sicr_cont.end(); ++itr){
        if(**itr == num){
            _sicr_cont.erase(itr);
            break;
        }
    }
    for(auto itr=_prm_cont.begin();itr != _prm_cont.end(); ++itr){
        if(**itr == num){
            _prm_cont.erase(itr);
            break;
        }
    }    
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
int MagicalContainer::size() const{
    return _size;
}
std::vector<int>& MagicalContainer::getContainer(){
    return _container;
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) : _container(other._container), _current_index(other._current_index) {}
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : _container(container), _current_index(0) {}
void MagicalContainer::AscendingIterator::setIndex(int idx){
    if(idx>this->_container.size()) throw invalid_argument("Index not in range.");
    this->_current_index = idx;
}


MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) : _container(other._container), _current_index(other._current_index) {}
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : _container(container), _current_index(0) {}
// MagicalContainer::SideCrossIterator::~SideCrossIterator(){}
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) : _container(other._container), _current_index(other._current_index) {}
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : _container(container), _current_index(0) {}
// MagicalContainer::PrimeIterator::~PrimeIterator(){}

bool ariel::isPrime(const int num){
    if(num<2) return false;
    if(num == 2||num==3) return true;
    for(int i=2;i<=sqrt(num);++i){
        if(num%i==0) return false;
    }
    return true;
}
