#include "MagicalContainer.hpp"
#include <stdexcept>
namespace ariel{
    bool comPtr(const int* a,const int* b){
        return *a < *b;
    }
    void MagicalContainer::addElement(int element){
        /**
         * adding element in order to vector 
         * finding index of the closest bigger number, return ptr to the index
         * insert new element in that index
        */
        auto pit = std::lower_bound(elements.begin(), elements.end(), element);
        elements.insert(pit, element);
        /**
         * check if element is prime if true-> add to primes vector
        */
       if(isPrime(element)){
            int *ptr_e = new int(element);
            auto prit = std::lower_bound(primes.begin(), primes.end(), ptr_e, comPtr);              //got help from friend about lower_bound
            primes.insert(prit,ptr_e);
            //-----------------------------------------------------------> CHECK order of ptr
       }
    }
    bool MagicalContainer::isPrime(int num){
        if(num <= 1) return false;
        for(int i = 2; i * i <= num; i++){
            if(num % i == 0) return false;
        }
        return true;
    }
    void MagicalContainer::removeElement(int element){
        auto ptr = std::find(elements.begin(), elements.end(), element);
        /** 
         * ptr type should be iterator
         * if ptr equals end of vector -> element not exist 
         */
        if(ptr != elements.end()){
            elements.erase(ptr);
        }
        else {
            throw std::runtime_error("not exist in container");
        }
        /**
         * in case element is also prime -> find and remove from prime vector
        */
        auto prim = std::find(primes.begin(), primes.end(), &element);  //--------------------------------> CHECK about & in elements
        if(prim != primes.end()) primes.erase(prim); //if not exist already throws before
    }
    void MagicalContainer::Iterator::checkTypes(const Iterator &other) const{
        if( this->type != other.getType()){
            throw std::runtime_error("different types");
        }
    }    
    void MagicalContainer::Iterator::checkContainers(const Iterator &other) const{
        if(this->container != other.container){
            throw std::runtime_error("different containers");
        }    
    }
    bool MagicalContainer::Iterator::operator<(const Iterator &other)const{
        checkTypes(other);
        checkContainers(other);
        return this->current_index < other.current_index;
    }
    bool MagicalContainer::Iterator::operator>(const Iterator &other)const{
        checkTypes(other);
        checkContainers(other);
        return this->current_index > other.current_index;        
    }    
    bool MagicalContainer::Iterator::operator==(const Iterator &other)const{
        checkTypes(other);
        checkContainers(other);
        return this->current_index == other.current_index;        
    }
    bool MagicalContainer::Iterator::operator!=(const Iterator &other)const{
        return !(*this == other);   
    }
    int MagicalContainer::SideCrossIterator::operator*()const{
        /**
         * vector is sorted, index is for iterator; position is place in vector
         * for every even index we output from begining+; fro every odd index the output is from the end
         * 
         * i=0 output first element; i=1 output size - 1/2 (=0) -1 (the last element)
         * i=2  (i/2 = 1)output second element from begining, i=3 output size - (3/2 = 1) -1 -> size-2 -> second to last/
         * */ 
        auto index = (current_index % 2 == 0) ? (current_index/2) : container->elements.size() - (current_index/2) -1;
        return container->elements.at(index);     
    }
    int MagicalContainer::PrimeIterator::operator*()const{
        auto ptr = container->primes.at(current_index);
        int val = *ptr;
        return val;        
    }
}

