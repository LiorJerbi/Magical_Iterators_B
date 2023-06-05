#pragma once

#include <vector>
#include <iostream>


namespace ariel {
    class MagicalContainer {
    private:
        std::vector<int> _container;
        std::vector<int*> _asc_cont;
        std::vector<int*> _sicr_cont;
        std::vector<int*> _prm_cont;
        int _size;

        MagicalContainer(MagicalContainer& other);
        MagicalContainer& operator=(const MagicalContainer &other) = default;
        MagicalContainer(MagicalContainer&& other) = delete;
        MagicalContainer& operator=(MagicalContainer&& other) = delete;
    public:
        MagicalContainer();
        ~MagicalContainer() = default;

        void addElement(int num);
        void removeElement(int num);
        int size() const;
        std::vector<int>& getContainer();
    
        class AscendingIterator {
            private:
                MagicalContainer& _container;
                int _current_index;

            public:
                AscendingIterator(const AscendingIterator& other);
                AscendingIterator(MagicalContainer& container);
                ~AscendingIterator() = default;
                AscendingIterator(AscendingIterator&& other) = default;
                AscendingIterator& operator=(AscendingIterator& other){
                    if (&_container != &(other._container)) {
                        throw std::runtime_error("Cannot assign iterators from different containers.");
                    }
                    _current_index = other._current_index;
                    return *this;
                }

                void setIndex(int idx);
                AscendingIterator& operator=(const AscendingIterator& other) {
                    _container = other._container;
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
                    return *_container._asc_cont.at(static_cast<std::vector<int>::size_type>(_current_index));
                }

                AscendingIterator& operator++() {
                    if(_current_index+1>_container._asc_cont.size()) throw std::runtime_error("Iterator Overflow");
                    else{
                        ++_current_index;}
                    return *this;
                }

                AscendingIterator begin() {
                    return AscendingIterator(_container);
                }

                AscendingIterator end() {
                    AscendingIterator ite(_container);
                    ite._current_index = ite._container._asc_cont.size();
                    return ite;
                }
        };

        class SideCrossIterator {

            private:
                MagicalContainer& _container;
                int _current_index;

            public:
                SideCrossIterator(const SideCrossIterator& other);
                SideCrossIterator(MagicalContainer& container);
                ~SideCrossIterator() = default;
                SideCrossIterator(SideCrossIterator&& other) = default;
                SideCrossIterator& operator=(SideCrossIterator& other){
                    if (&_container != &(other._container)) {
                        throw std::runtime_error("Cannot assign iterators from different containers.");
                    }
                    _current_index = other._current_index;
                    return *this;
                }

                void setIndex(int idx){_current_index = idx;}
                SideCrossIterator& operator=(const SideCrossIterator& other) {
                    _container = other._container;
                    _current_index = other._current_index;
                    return *this;
                }

                bool operator==(const SideCrossIterator& other) const {
                    return _current_index == other._current_index;
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
                    return *_container._sicr_cont.at(static_cast<std::vector<int>::size_type>(_current_index));
                }

                SideCrossIterator& operator++() {
                    if(_current_index+1>_container._sicr_cont.size()) throw std::runtime_error("Iterator Overflow");
                    else{
                        ++_current_index;}
                    return *this;
                }

                SideCrossIterator begin() {
                    return SideCrossIterator(_container);
                }

                SideCrossIterator end() {
                    SideCrossIterator ite(*this);
                    ite._current_index = ite._container._sicr_cont.size();
                    return ite;
                }
        };

        class PrimeIterator {
            private:
                MagicalContainer& _container;
                int _current_index;

            public:
                PrimeIterator(const PrimeIterator& other);
                PrimeIterator(MagicalContainer& container);
                ~PrimeIterator() = default;
                PrimeIterator(PrimeIterator&& other) = default;
                PrimeIterator& operator=(PrimeIterator& other){
                    if (&_container != &(other._container)) {
                        throw std::runtime_error("Cannot assign iterators from different containers.");
                    }
                    _current_index = other._current_index;
                    return *this;
                }

                void setIndex(int idx){_current_index = idx;}
                PrimeIterator& operator=(const PrimeIterator& other) {
                    _container = other._container;
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
                    if(_current_index+1>_container._prm_cont.size()) throw std::runtime_error("Iterator Overflow");
                    else{
                        ++_current_index;}
                    return *this;
                }

                PrimeIterator begin() {
                    return PrimeIterator(_container);
                }

                PrimeIterator end() {
                    PrimeIterator ite(*this);
                    ite._current_index = ite._container._prm_cont.size();
                    return ite;
                }
        };

    };
    bool isPrime(const int num);
}
