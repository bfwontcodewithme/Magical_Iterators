#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include <vector>

namespace ariel {
    class MagicalContainer{
        private:
        std::vector <int> elements;
        public:
        MagicalContainer();
        void addElement(int element );
        void removeElement(int element);
        size_t size(){return elements.size();}     //protects from int overflow
        ~MagicalContainer();

        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;                  
    };
    class MagicalContainer::AscendingIterator{
        private:
            MagicalContainer& container;
            size_t current_index;
        public:
            AscendingIterator(MagicalContainer& curr_container, size_t current = 0) : container(curr_container), current_index(current) {};
            AscendingIterator begin(){ return AscendingIterator(container, 0);}
            AscendingIterator end(){ return AscendingIterator(container, container.size());}
            
            int operator*()const{ return container.elements.at(current_index);}
            bool operator<(const AscendingIterator& other)const{return true;}
            bool operator>(const AscendingIterator& other)const{return true;}
            bool operator ==(const AscendingIterator& other)const{return current_index == other.current_index;}
            bool operator !=(const AscendingIterator& other)const{return !(*this == other);}
            AscendingIterator operator++(){
                ++current_index;
                return *this;
            }
            AscendingIterator &operator=(AscendingIterator& other){return *this;}


    };
    class MagicalContainer::SideCrossIterator{
        private:
            MagicalContainer& container;
            size_t current_index;
            public:
            SideCrossIterator(MagicalContainer& curr_container, size_t current = 0) : container(curr_container), current_index(current) {};
            SideCrossIterator begin(){ return SideCrossIterator(container, 0);}
            SideCrossIterator end(){ return SideCrossIterator(container, container.size());}
            int operator*()const{ return container.elements.at(current_index);}
            bool operator<(SideCrossIterator& other)const{return true;}
            bool operator>(SideCrossIterator& other)const{return true;}
            bool operator ==(SideCrossIterator& other)const{return current_index == other.current_index;}
            bool operator !=(SideCrossIterator& other)const{return !(*this == other);}
            SideCrossIterator operator++(){
                ++current_index;
                return *this;
            }
            SideCrossIterator &operator=(SideCrossIterator& other){return *this;}
    };
    class MagicalContainer::PrimeIterator{
        private:
            MagicalContainer& container;
            size_t current_index;
            public:
            PrimeIterator(MagicalContainer& curr_container, size_t current = 0) : container(curr_container), current_index(current) {};
            PrimeIterator begin(){ return PrimeIterator(container, 0);}
            PrimeIterator end(){ return PrimeIterator(container, container.size());}
            int operator*()const{ return container.elements.at(current_index);}
            bool operator<(PrimeIterator& other)const{return true;}
            bool operator>(PrimeIterator& other)const{return true;}
            bool operator ==(PrimeIterator& other)const{return current_index == other.current_index;}
            bool operator !=(PrimeIterator& other)const{return !(*this == other);}
            PrimeIterator operator++(){
                ++current_index;
                return *this;
            }
            PrimeIterator &operator=(PrimeIterator& other){return *this;}
    };

}
#endif