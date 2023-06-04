#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

namespace ariel {
    class MagicalContainer{
        int element;
        int size;

        MagicalContainer(){};
        ~MagicalContainer(){};

        int addElement(int element ){};
        int removeElement(int element){};
        int getSizeContainer(){ return size; }
        int getElement(){};
        
        class Iterator{

            int* iter;

            Iterator(){};
            Iterator(Iterator &other){}
            ~Iterator(){};
            int operator=(){}
        };
        class AscendingIterator : public Iterator{};
        class SideCrossIterator : public Iterator{};
        class PrimeIterator : public Iterator{};                    
    };
}
#endif