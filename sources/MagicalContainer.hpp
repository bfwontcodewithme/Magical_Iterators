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
                MagicalContainer* container;
                size_t current_index;


            public:
                int type;             // 1-ascending, 2-sidecross, 3-prime
                Iterator(MagicalContainer &curr_container, size_t current = 0, int type = ascend): container(&curr_container), current_index(current), type(type){};
                Iterator(const Iterator& other) : container(other.container), current_index(other.current_index){};
                int getType()const{return this->type;}
                void checkTypes(const Iterator& other) const {
                    if( this->type != other.getType()){
                        throw std::runtime_error("different types");
                    }
                }
                void checkContainers(const Iterator& other)const{
                    if(this->container != other.container){
                        throw std::runtime_error("different containers");
                    }
                }
                bool operator<(const Iterator& other)const{
                    checkTypes(other);
                    checkContainers(other);
                    return this->current_index < other.current_index;
                }
                bool operator>(const Iterator& other)const{
                    checkTypes(other);
                    checkContainers(other);
                    return this->current_index > other.current_index;
                }
                bool operator ==(const Iterator& other)const{
                    checkTypes(other);
                    checkContainers(other);
                    return this->current_index == other.current_index;
                }
                bool operator !=(const Iterator& other)const{
                    return !(*this == other);
                }

        };
        /*----------------------------------------------end class iterator--------------------------------------------------------------------------*/
        public:
            MagicalContainer() = default;
            ~MagicalContainer(){
                for (int* ptr : primes){
                    delete ptr;
                }
            };
            MagicalContainer(const MagicalContainer &other) = default;
            void addElement(int element);
            void removeElement(int element);
            size_t size(){return elements.size();}     //protects from int overflow
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
            AscendingIterator operator++(){
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
            int operator*()const{
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
            SideCrossIterator &operator=(SideCrossIterator& other){
                if(*this != other){
                    this->current_index = other.current_index;
                }
                return *this;
            }
            SideCrossIterator operator++(){
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
            int operator*()const{
                auto ptr = container->primes.at(current_index);
                int val = *ptr;
                return val;
            }
            PrimeIterator &operator=(PrimeIterator& other){
                if(*this != other){
                    this->current_index = other.current_index;
                }
                return *this;
            };
            PrimeIterator operator++(){
                if(current_index == container->size()){
                        throw std::runtime_error("vector ended");
                }
                ++current_index;
                return *this;
            }
    };

}

#endif