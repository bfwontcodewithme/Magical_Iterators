#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include <vector>
#include <stdexcept>
int const ascend =1;
int const sidecross =2;
int const prime =3;
/**
 * 
*/
namespace ariel {
    class MagicalContainer{
        
        private:
        std::vector <int> elements;         //vector with elements of container
        std::vector <int*> primes;          //vector of ptrs to prime values in elements
        /*--------------------------------------------------class iterator--------------------------------------------------------------------------*/
        class Iterator{
            protected:
                MagicalContainer* container;        //sub iterator needs access 
                size_t current_index;


            public:
                int type;             // 1-ascending, 2-sidecross, 3-prime
                Iterator(MagicalContainer &curr_container, size_t current = 0, int type = ascend): container(&curr_container), current_index(current), type(type){};
                Iterator(const Iterator& other) : container(other.container), current_index(other.current_index){};
                
                int getType()const{return this->type;}
                void checkTypes(const Iterator& other) const;
                void checkContainers(const Iterator& other)const;
                
                bool operator<(const Iterator& other)const;
                bool operator>(const Iterator& other)const;
                bool operator ==(const Iterator& other)const;
                bool operator !=(const Iterator& other)const;
        };
        /*----------------------------------------------end class iterator--------------------------------------------------------------------------*/
        public:
            MagicalContainer() = default;
            ~MagicalContainer(){
                for (int* ptr : primes){
                    delete ptr;
                }
            };
            void addElement(int element);
            void removeElement(int element);
            size_t size(){return elements.size();}     //type is size_t ->protects from int overflow
            bool isPrime(int num);

            class AscendingIterator;
            class SideCrossIterator;
            class PrimeIterator;                  
    };

    
    class MagicalContainer::AscendingIterator : public MagicalContainer::Iterator{      //MagicalContainer is already sorted 

        public:
            AscendingIterator(MagicalContainer &curr_container, size_t current = 0) : Iterator(curr_container, current, ascend) {};
            AscendingIterator(const AscendingIterator& other) : Iterator(other){}
            ~AscendingIterator(){};
            AscendingIterator begin(){return AscendingIterator(*container, 0);}
            AscendingIterator end(){return AscendingIterator(*container, container->elements.size());}
            int operator*()const{ return container->elements.at(current_index);}
            AscendingIterator &operator=(AscendingIterator& other){
                if(*this != other){
                    this->current_index = other.current_index;
                }
                return *this;
            }
            AscendingIterator &operator++(){
                if(current_index == container->size()){
                    throw std::runtime_error("vector ended");
                }
                ++current_index;
                return *this;
            }  
    };
    class MagicalContainer::SideCrossIterator : public MagicalContainer::Iterator{

        public:
            SideCrossIterator(MagicalContainer &curr_container, size_t current = 0) : Iterator(curr_container, current, sidecross){};
            ~SideCrossIterator(){};
            SideCrossIterator(const SideCrossIterator& other) : Iterator(other){};
            SideCrossIterator begin(){return SideCrossIterator(*container, 0);}
            SideCrossIterator end(){return SideCrossIterator(*container, container->elements.size());}
            int operator*()const;
            SideCrossIterator &operator=(SideCrossIterator& other){
                if(*this != other){
                    this->current_index = other.current_index;
                }
                return *this;
            }
            SideCrossIterator &operator++(){
                if(current_index == container->size()){
                        throw std::runtime_error("vector ended");
                }
                ++current_index;
                return *this;
            }
    };
    class MagicalContainer::PrimeIterator : public MagicalContainer::Iterator{

        public:
            PrimeIterator(MagicalContainer &curr_container, size_t current = 0) : Iterator(curr_container, current, prime) {};
            ~PrimeIterator(){};
            PrimeIterator(const PrimeIterator& other): Iterator(other){};
            PrimeIterator begin(){return PrimeIterator(*container, 0);}
            PrimeIterator end(){return PrimeIterator(*container, container->primes.size());}
            int operator*()const;
            PrimeIterator &operator=(PrimeIterator& other){
                if(*this != other){
                    this->current_index = other.current_index;
                }
                return *this;
            };
            PrimeIterator &operator++(){
                if(current_index == container->primes.size()){
                        throw std::runtime_error("vector ended");
                }
                ++current_index;
                return *this;
            }
    };
}

#endif