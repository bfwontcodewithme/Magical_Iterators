#include "sources/MagicalContainer.hpp"
#include "doctest.h"
#include <stdexcept>

using namespace ariel;
// Testing MagicalContainer Methods
TEST_CASE("Adding Elements"){
    MagicalContainer container;
    container.addElement(1);
    CHECK(container.size() == 1);
    container.addElement(22);
    container.addElement(333);
    CHECK(container.size() == 3);
}
TEST_CASE("Remove Elements"){
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    CHECK_NOTHROW(container.removeElement(2));
    CHECK(container.size() == 1);
    CHECK_THROWS(container.removeElement(3));
    CHECK(container.size() == 1);
}
TEST_CASE("AscendingIterator"){
    MagicalContainer container;
    //checking with empty container
    MagicalContainer::AscendingIterator it(container);
    CHECK(it == it.end());
    //adding elements - container not empy anymore
    container.addElement(1);
    container.addElement(22);
    container.addElement(3);
    container.addElement(44);
    // checking iterating the right order
    MagicalContainer::AscendingIterator iter(container);
    CHECK(*iter == 1);
    CHECK(*iter == 1);
    ++iter;
    CHECK(*iter == 3);
    ++iter;
    CHECK(*iter == 22);
    ++iter;
    CHECK(*iter == 44);
    ++iter;
    CHECK(iter == iter.end());
}
TEST_CASE("Ascending with negeative value"){
    MagicalContainer container;
    container.addElement(1);
    container.addElement(-1);
    container.addElement(0);
    MagicalContainer::AscendingIterator aiter(container);
    CHECK(*aiter == -1);
    ++aiter;
    CHECK(*aiter == 0);
    ++aiter;
    CHECK(*aiter == 1);
    ++aiter;
    CHECK(aiter == aiter.end());
}

TEST_CASE("SideCrossIterator"){
    MagicalContainer container;
    //checking with empty container
    MagicalContainer::SideCrossIterator it(container);
    CHECK(it == it.end());
    //adding elements - container not empy anymore
    container.addElement(1);
    container.addElement(22);
    container.addElement(3);
    container.addElement(44);
    // checking iterating the right order
    MagicalContainer::SideCrossIterator iter(container);
    CHECK(*iter == 1);
    CHECK(*iter == 1);
    ++iter;
    CHECK(*iter == 44);
    ++iter;
    CHECK(*iter == 22);
    ++iter;
    CHECK(*iter == 3);
    ++iter;
    CHECK(iter == iter.end());
}
TEST_CASE("sidecross with single element"){
    MagicalContainer container;
    container.addElement(2);
    MagicalContainer::SideCrossIterator sciter(container);
    CHECK(*sciter == 2);
    ++sciter;
    CHECK(sciter == sciter.end());
}

TEST_CASE("PrimeIterator"){
    MagicalContainer container;
    //checking with empty container
    MagicalContainer::PrimeIterator it(container);
    CHECK(it == it.end());
    //adding elements - container not empy anymore
    container.addElement(1);
    container.addElement(22);
    container.addElement(3);
    container.addElement(44);
    container.addElement(17);
    // checking iterating the right order
    MagicalContainer::PrimeIterator iter(container);
    CHECK(*iter == 1);
    CHECK(*iter == 1);
    ++iter;
    CHECK(*iter == 3);
    ++iter;
    CHECK(*iter == 17);
    ++iter;
    CHECK(iter == iter.end());
}
TEST_CASE("Prime iterator with no primes"){
    MagicalContainer container;
    container.addElement(4);
    container.addElement(6);
    container.addElement(8);

    MagicalContainer::PrimeIterator piter(container);
    CHECK(piter == piter.end());
}
TEST_CASE("all iterators with one container"){
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    MagicalContainer::AscendingIterator ait(container);
    MagicalContainer::SideCrossIterator scit(container);
    MagicalContainer::PrimeIterator pit(container);
    CHECK(*ait == 1);
    CHECK(*scit == 1);
    CHECK(*pit == 2);
    ++ait;
    ++scit;
    ++pit;
    CHECK(*ait == 2);
    CHECK(*scit == 14);
    CHECK(*pit == 5);
    ++ait;
    ++scit;
    ++pit;
    CHECK(*ait == 4);
    CHECK(*scit == 2);
    CHECK(pit == pit.end());
    ++ait;
    ++scit;
    CHECK(*ait == 5);
    CHECK(*scit == 5);
    ++ait;
    ++scit;
    CHECK(*ait == 14);
    CHECK(*scit == 4); 
    ++ait;
    ++scit;
    CHECK(ait == ait.end());
    CHECK(scit == scit.end()); 
}
TEST_CASE("index boundry"){
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Ascending"){
        MagicalContainer::AscendingIterator ait(container);
        while(ait != ait.end()){
            ++ait;
        }
        CHECK_THROWS_AS(++ait, std::runtime_error);
    }
    SUBCASE("SideCross"){
        MagicalContainer::SideCrossIterator scit(container);
        while(scit != scit.end()){
            ++scit;
        }
        CHECK_THROWS_AS(++scit, std::runtime_error);
    }
    SUBCASE("Prime"){
        MagicalContainer::PrimeIterator pit(container);
        while(pit != pit.end()){
            ++pit;
        }
        CHECK_THROWS_AS(++pit, std::runtime_error);
    }
}
