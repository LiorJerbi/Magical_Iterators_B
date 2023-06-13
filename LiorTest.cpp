#include <iostream>
#include <string>
#include "sources/MagicalContainer.hpp"
#include "doctest.h"

using namespace ariel;
using namespace std;

TEST_SUITE("Magical Container Methods:"){
    MagicalContainer container;

    TEST_CASE("add/remove/size methods"){
        CHECK(container.size() == 0);
        CHECK_THROWS_AS(container.removeElement(2),runtime_error);  //can't remove from empty container
        CHECK_NOTHROW(container.addElement(1));         
        
        container.addElement(7);
        container.addElement(5);
        CHECK_EQ(container.size(),3);
        
        CHECK_NOTHROW(container.removeElement(1));  //removing exist element should not throw
        CHECK_EQ(container.size(),2);
        
        CHECK_THROWS(container.removeElement(1)); // removing elemnt that already removed should throw.       
        
    }

}
TEST_SUITE("Iterators Methods:"){

    TEST_CASE("AscendingIterator:"){

        //empty iterator
        MagicalContainer emptycont;
        CHECK_NOTHROW(MagicalContainer::AscendingIterator emIt(emptycont)); //assigning empty container should not throw
        
        //empty iterator, end, begin should be equal.
        MagicalContainer::AscendingIterator emIt(emptycont);
        CHECK_EQ(emIt,emIt.end());
        CHECK_EQ(emIt.begin(),emIt.end());

        //Iterator demo.
        MagicalContainer container;
        container.addElement(5);
        container.addElement(2);
        container.addElement(4);
        container.addElement(1);
        container.addElement(14);

        MagicalContainer::AscendingIterator asIt(container);
        auto it = asIt.begin();
        auto itTest = it;
        
        //operators tests
        CHECK_EQ(itTest,asIt.begin());  //operator= test
        CHECK_NOTHROW(++itTest);        //operator++ prefix test
        CHECK_EQ(*it,1);                //begin should be 1 on Asc order (and operator* test)
        CHECK(it<itTest);               //operator< test  (index wise)
        CHECK(itTest>it);               //operator> test  (index wise)
        CHECK(it!=itTest);              //operator != test
        CHECK_FALSE(it==itTest);        //operator == test
        
        //values comparasion
        ++it;
        CHECK_EQ(*it,2);    
        ++it;
        CHECK_EQ(*it,4);
        ++it;
        CHECK_EQ(*it,5);

        CHECK_NE(it,asIt.end());        //still not in the end.
        
        container.addElement(7);        //adding element mid running should reflect in iterator
        CHECK(container.size() == 6);        
        
        ++it;
        CHECK_EQ(*it,7);    
        ++it;
        CHECK_EQ(*it,14);    
        ++it;
        CHECK_EQ(it,asIt.end());
    }   
    TEST_CASE("SideCrossIterator:"){

        //empty iterator
        MagicalContainer emptycont;
        CHECK_NOTHROW(MagicalContainer::SideCrossIterator emIt(emptycont)); //assigning empty container should not throw
        
        //empty iterator, end, begin should be equal.
        MagicalContainer::SideCrossIterator emIt(emptycont);
        CHECK_EQ(emIt,emIt.end());
        CHECK_EQ(emIt.begin(),emIt.end());

        //Iterator demo.
        MagicalContainer container;
        container.addElement(5);
        container.addElement(2);
        container.addElement(4);
        container.addElement(1);
        container.addElement(14);
        MagicalContainer::SideCrossIterator scIt(container);
        auto it = scIt.begin();
        auto itTest = it;
        
        //operators tests
        CHECK_EQ(itTest,scIt.begin());  //operator= test
        CHECK_NOTHROW(++itTest);        //operator++ prefix test
        CHECK_EQ(*it,1);                //begin should be 1 on SideCross order (and operator* test)
        CHECK(it<itTest);               //operator< test  (index wise)
        CHECK(itTest>it);               //operator> test  (index wise)
        auto itTest2 = itTest;
        ++itTest2;
        CHECK(itTest2<itTest);       //in sidecross ++ index wise not always bigger.
        CHECK(it!=itTest);              //operator != test
        CHECK_FALSE(it==itTest);        //operator == test
        
        //values comparasion
        ++it;
        CHECK_EQ(*it,14);    
        ++it;
        CHECK_EQ(*it,2);
        ++it;
        CHECK_EQ(*it,5);

        CHECK_NE(it,scIt.end());        //still not in the end.
   
        ++it;
        CHECK_EQ(*it,4);
        ++it;
        CHECK_EQ(it,scIt.end());
    }
    TEST_CASE("PrimeIterator:"){
        MagicalContainer container;
        container.addElement(5);
        container.addElement(2);
        container.addElement(4);
        container.addElement(1);
        container.addElement(14);
        MagicalContainer::PrimeIterator prIt(container);
        auto it = prIt.begin();
        auto itTest = it;
        
        //operators tests
        CHECK_EQ(itTest,prIt.begin());  //operator= test
        CHECK_NOTHROW(++itTest);        //operator++ prefix test
        CHECK_EQ(*it,2);                //begin should be 2 on Prime order (and operator* test)
        CHECK(it<itTest);               //operator< test  (index wise)
        CHECK(itTest>it);               //operator> test  (index wise)
        CHECK(it!=itTest);              //operator != test
        CHECK_FALSE(it==itTest);        //operator == test
        
        //values comparasion
        ++it;
        CHECK_EQ(*it,5);    
        CHECK_NE(it,prIt.end());        //still not in the end.
        
        container.addElement(7);        //adding element mid running should reflect in iterator
        CHECK(container.size() == 6);        
        
        ++it;
        CHECK_EQ(*it,7);  
        ++it;
        CHECK_EQ(it,prIt.end());    
    }
}