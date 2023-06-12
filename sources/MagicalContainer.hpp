#pragma once

#include <vector>
#include <iostream>


namespace ariel {
    class MagicalContainer {
    private:
        std::vector<int> _container;
        std::vector<int*> _prm_cont;
        int _size;

        MagicalContainer(MagicalContainer& other);
        MagicalContainer& operator=(const MagicalContainer &other) = default;
        MagicalContainer(MagicalContainer&& other) = delete;
        MagicalContainer& operator=(MagicalContainer&& other) = delete;
    public:
        MagicalContainer();
        ~MagicalContainer();

        void addElement(int num);
        void removeElement(int num);
        int size() const{return _size;}
        std::vector<int>& getContainer(){return _container;}
    
        class AscendingIterator {
            private:
                MagicalContainer& _container;
                int _current_index;

                AscendingIterator& operator=(AscendingIterator&& other) = delete;

            public:
                //Constructors & Destructor
                AscendingIterator(const AscendingIterator& other);
                AscendingIterator(MagicalContainer& container);
                ~AscendingIterator() = default;
                AscendingIterator(AscendingIterator&& other) = default;

                void setIndex(int idx);

                //Operators

                AscendingIterator& operator=(const AscendingIterator& other){
                    if (&_container != &(other._container)) {
                        throw std::runtime_error("Cannot assign iterators from different containers.");
                    }
                    _current_index = other._current_index;
                    return *this;
                }
                bool operator==(const AscendingIterator& other) const {
                    return _current_index == other._current_index;
                }

                bool operator!=(const AscendingIterator& other) const {
                    return !(*this == other);
                }

                bool operator>(const AscendingIterator& other) const {
                    return _current_index > other._current_index;
                }

                bool operator<(const AscendingIterator& other) const {
                    return _current_index < other._current_index;
                }

                int& operator*() const {
                    return _container._container.at(static_cast<std::vector<int>::size_type>(_current_index));
                }

                AscendingIterator& operator++() {
                    if(_current_index+1>_container.size()) {throw std::runtime_error("Iterator Overflow");}
                    ++_current_index;
                    return *this;
                }

                AscendingIterator begin() {
                    return AscendingIterator(_container);
                }

                AscendingIterator end() {
                    AscendingIterator ite(_container);
                    ite._current_index = ite._container.size();
                    return ite;
                }
        };

        class SideCrossIterator {

            private:
                MagicalContainer& _container;
                int _current_index,counter;
                
                SideCrossIterator& operator=(SideCrossIterator&& other) = delete;

            public:
                //Constructors & Destructor
                SideCrossIterator(const SideCrossIterator& other);
                SideCrossIterator(MagicalContainer& container);
                ~SideCrossIterator() = default;
                SideCrossIterator(SideCrossIterator&& other) = default;

                void setIndex(int idx);

                //Operators
                SideCrossIterator& operator=(const SideCrossIterator& other){
                    if (&_container != &(other._container)) {
                        throw std::runtime_error("Cannot assign iterators from different containers.");
                    }
                    _current_index = other._current_index;
                    counter=other.counter;
                    return *this;
                }
                bool operator==(const SideCrossIterator& other) const {
                    return  (counter == other.counter);
                }

                bool operator!=(const SideCrossIterator& other) const {
                    return !(*this == other);
                }

                bool operator>(const SideCrossIterator& other) const {
                    return _current_index > other._current_index;
                }

                bool operator<(const SideCrossIterator& other) const {
                    return _current_index < other._current_index;
                }

                int& operator*() const {
                    return _container._container.at(static_cast<std::vector<int>::size_type>(_current_index));
                }

                SideCrossIterator& operator++() {
                    if(counter+1>_container._container.size()){ throw std::runtime_error("Iterator Overflow");}

                    int contsize = _container.size();

                    if (counter % 2 == 0) {
                        _current_index = contsize - (counter/2) - 1;
                    } else {
                        _current_index = (counter/2)+1;
                    }
                    counter++;
                    return *this;
                }

                SideCrossIterator begin() {
                    return SideCrossIterator(_container);
                }

                SideCrossIterator end() {
                    SideCrossIterator ite(*this);
                    ite.counter = ite._container.size();
                    return ite;
                }
        };

        class PrimeIterator {
            private:
                MagicalContainer& _container;
                int _current_index;

                PrimeIterator& operator=(PrimeIterator&& other) = delete;

            public:
                //Constructors & Destructor
                PrimeIterator(const PrimeIterator& other);
                PrimeIterator(MagicalContainer& container);
                ~PrimeIterator() = default;
                PrimeIterator(PrimeIterator&& other) = default;

                void setIndex(int idx);

                //Operators.
                PrimeIterator& operator=(const PrimeIterator& other){
                    if (&_container != &(other._container)) {
                        throw std::runtime_error("Cannot assign iterators from different containers.");
                    }
                    _current_index = other._current_index;
                    return *this;
                }

                bool operator==(const PrimeIterator& other) const {
                    return _current_index == other._current_index;
                }

                bool operator!=(const PrimeIterator& other) const {
                    return !(*this == other);
                }

                bool operator>(const PrimeIterator& other) const {
                    return _current_index > other._current_index;
                }

                bool operator<(const PrimeIterator& other) const {
                    return _current_index < other._current_index;
                }

                int& operator*() const {
                    return *_container._prm_cont.at(static_cast<std::vector<int>::size_type>(_current_index));
                }

                PrimeIterator& operator++() {
                    if(_current_index+1>_container._prm_cont.size()) {throw std::runtime_error("Iterator Overflow");}
                    
                    ++_current_index;
                    return *this;
                }

                PrimeIterator begin() {
                    return PrimeIterator(_container);
                }

                PrimeIterator end() {
                    PrimeIterator ite(*this);
                    ite._current_index = static_cast<int>(ite._container._prm_cont.size());
                    return ite;
                }
        };

    };
    bool isPrime(int num);
}
