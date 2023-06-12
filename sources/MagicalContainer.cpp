#include "MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

bool isPrime(int num) {
    if (num <= 1)
        return false;
    // Check for divisibility from 2 to sqrt(num)
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}



namespace ariel {
    void MagicalContainer::add_element_inc(){
        element_inc.clear();
        for (auto it = element_major.begin(); element_major.end() != it; ++it)
        {
            element_inc.push_back(&(*it));
        }

        sort(element_inc.begin(), element_inc.end(), [](int* a, int* b) {return *a < *b;});
    }

    void MagicalContainer::add_element_cut(){
        auto end = --element_major.end();
        auto begin = element_major.begin();
        element_cut.clear();

        while(begin < end)
        {
            element_cut.push_back(&(*begin));
            begin++;
            element_cut.push_back(&(*end));
            end--;
        }
        if (begin == end)
        {
            element_cut.push_back(&(*begin));
        }
    }
    
    void MagicalContainer::add_element_prime(){
        element_p.clear();
        for (auto it = element_major.begin(); element_major.end() != it; ++it)
        {
            if (isPrime(*it))
            {
                element_p.push_back(&(*it));
            }
        }
    }

    void MagicalContainer::addElement(int e) {
        if (element_major.end() != find(element_major.begin(), element_major.end(), e) ) {
            return;
        }

        element_major.push_back(e);

        add_element_inc();

        add_element_cut();

        add_element_prime();

    }

    void MagicalContainer::removeElement(int e)
    {
        auto it = find(element_major.begin(), element_major.end(), e);
        if (it == element_major.end())
        {
            throw runtime_error("runtime error");
        }
        element_major.erase(it);

        add_element_inc();

        add_element_cut();

        add_element_prime();
    }


    int MagicalContainer::size() const {
        return this->element_major.size();
    }

    vector<int> MagicalContainer::getElements() const{
        return this->element_major;
    }


    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& cont)
        : mc(cont), iterator_inc(cont.element_inc.begin()), location(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& it)
        : mc(it.mc), iterator_inc(it.iterator_inc), location(it.location) {}

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if(iterator_inc == mc.element_inc.end())
        {
            throw runtime_error("runtime error");
        }
        ++iterator_inc;
        ++location;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& it) const {
        if(&mc == &it.mc)
        {
            return this->location == it.location;
        }
        throw invalid_argument("Invalid argument");
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& it) const {
        if(&mc == &it.mc) 
        {
            return this->location != it.location;
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& it) const {
        if(&mc == &it.mc) 
        {
            return this->location > it.location;
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& it) const {
        if(&mc == &it.mc) 
        {
            return this->location < it.location;
            
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& it)
    {
        if (&mc == &it.mc)
        {
            iterator_inc = it.iterator_inc;
            location = it.location;
            return *this;
        }
        throw runtime_error("Iterators are pointing at different containers");
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        
        if(iterator_inc == mc.element_inc.end())
        {
         throw out_of_range("Out of range");   
        }
        return **iterator_inc;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin(){
        iterator_inc = mc.element_inc.begin();
        location = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end() {
        iterator_inc = mc.element_inc.end();
        location = mc.element_inc.size();
        return *this;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& cont)
        : mc(cont), iterator_cut(cont.element_cut.begin()), location(0){}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& it)
        : mc(it.mc), iterator_cut(it.iterator_cut),
        location(it.location){}


    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if(iterator_cut == mc.element_cut.end())
        {
            throw runtime_error("Out of range");
        }
        ++iterator_cut;
        ++location;
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& it) const {
        if(&mc == &it.mc) 
        {
           return this->location == it.location;
        }
         throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& it) const {
        if(&mc == &it.mc) 
        {
          return this->location != it.location;
        } 
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& it) const {
        if(&mc == &it.mc) 
        {
           return this->location > it.location;
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& it) const {
        if(&mc == &it.mc) 
        {
            return this->location < it.location;
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& it)
    {
        if (&it.mc == &mc)
        {
            iterator_cut = it.iterator_cut;
            return *this;       
        }
        throw runtime_error("Iterators are pointing at different containers");
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if(iterator_cut == mc.element_cut.end())
        {
            throw out_of_range("Out of range");
        }
        return **iterator_cut;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator:: begin(){
        iterator_cut = mc.element_cut.begin();
        location = 0;
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator:: end() {
        location = mc.element_cut.size();
        iterator_cut = mc.element_cut.end();
        return *this;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& cont)
        : mc(cont), iterator_p(cont.element_p.begin()), location(0) {}


    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& it)
    : mc(it.mc), iterator_p(it.iterator_p), location(it.location) {}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if(mc.element_p.end() == iterator_p)
        {
            throw runtime_error("runtime error");
        }
        ++location;
        ++iterator_p;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& it) const {
        if(&it.mc == &mc ) 
        {
            return this->location == it.location;
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& it) const {
        if(&it.mc == &mc) 
        {
            return this ->location != it.location;
        }
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& it) const {
        if(&it.mc == &mc) 
        {
            return this->location > it.location;
        }    
        throw invalid_argument("Iterators are pointing at different containers");
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& it) const {
        if(&mc == &it.mc) 
        {
            return this->location < it.location;
        }        
        throw invalid_argument("Iterators are pointing at different containers");
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& it)
    {
        if (&mc == &it.mc)
        {
            iterator_p = it.iterator_p;
            location = it.location;
            return *this;
        }
        throw runtime_error("Iterators are pointing at different containers");
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        if(iterator_p == mc.element_p.end())
        {
            throw out_of_range("Out of range");
        }
        return **iterator_p;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator:: begin(){
        location = 0;
        iterator_p = mc.element_p.begin();
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator:: end(){
        location = mc.element_p.size();
        iterator_p = mc.element_p.end();
        return *this;
    }
} 

