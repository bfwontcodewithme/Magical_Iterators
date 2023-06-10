#include "MagicalContainer.hpp"
#include <stdexcept>
namespace ariel{
    bool comPtr(const int* a,const int* b){
        return *a < *b;
    }
    void MagicalContainer::addElement(int element)
    {
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
            auto prit = std::lower_bound(primes.begin(), primes.end(), ptr_e, comPtr);
            primes.insert(prit,ptr_e);
            //-----------------------------------------------------------> CHECK order of ptr
       }
    }
    bool MagicalContainer::isPrime(int num)
    {
        if(num <= 1) return false;
        for(int i = 2; i * i <= num; i++){
            if(num % i == 0) return false;
        }
        return true;
    }

    void MagicalContainer::removeElement(int element)
    {
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
}