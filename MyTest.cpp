

//including the necassery files.
#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <iostream>

using namespace std;
using namespace ariel;


// testing the basic functionality of addElement and removeElement methods, as well as checking the size of the container.
TEST_CASE("Test 1 - MagicalContainer::addElement and MagicalContainer::removeElement") {
	MagicalContainer mc; //creating empty instance of MagicalContainer.
	CHECK_EQ(mc.size(), 0); //check that the size is 0 at this point.

	mc.addElement(1);//add the element 1
	CHECK_EQ(mc.size(), 1);//check the size if correct

	mc.addElement(2);//add
	mc.addElement(3);//add

	CHECK_EQ(mc.size(), 3); //check size if correct

	mc.removeElement(2); //removing element
	CHECK_EQ(mc.size(), 2); // check size after remove

	mc.removeElement(1);
	mc.removeElement(3);

	CHECK_EQ(mc.size(), 0);
}


TEST_CASE("Test 2 - Iterator Sorted") {
	MagicalContainer mc; //creating empty instance of MagicalContainer.
	mc.addElement(3); //add 3.
	mc.addElement(4); //add 4.
 	mc.addElement(2); // add 2.

	MagicalContainer::AscendingIterator ascIter(mc); // creating instance of ascending iterator.

	CHECK_EQ(*ascIter, 2); //checking if the first element returned by the pointer to iterator is 2.
	++ascIter; // point to the next.
	CHECK_EQ(*ascIter, 3); //checking if it pointer now point to 3 after promoting the pointer.
	++ascIter; // point to the next
	CHECK_EQ(*ascIter, 4); //checking if it pointer now point to 4 after promoting the pointer
	++ascIter; // point to the next
	CHECK_EQ(ascIter, ascIter.end());//check if iterator has reached its end
}

TEST_CASE("Test 3 - Iterator SideCross") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::SideCrossIterator crossIter(mc);

	CHECK_EQ(*crossIter, 2);
	++crossIter;
	CHECK_EQ(*crossIter, 4);
	++crossIter;
	CHECK_EQ(*crossIter, 3);
	++crossIter;
	CHECK_EQ(crossIter, crossIter.end());
}

TEST_CASE("Test 4 - Iterator Prime") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::PrimeIterator primesIter(mc);

	CHECK_EQ(*primesIter, 2);
	++primesIter;
	CHECK_EQ(*primesIter, 3);
	++primesIter;
	CHECK_EQ(primesIter, primesIter.end());
}

TEST_CASE("Test 5 - Check iterators comparison") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::AscendingIterator ascIter1(mc);
	MagicalContainer::AscendingIterator ascIter2(mc);
	MagicalContainer::SideCrossIterator crossIter1(mc);
	MagicalContainer::SideCrossIterator crossIter2(mc);
	MagicalContainer::PrimeIterator primesIter1(mc);
	MagicalContainer::PrimeIterator primesIter2(mc);

	CHECK_EQ(ascIter1, ascIter2);
	CHECK_EQ(crossIter1, crossIter2);
	CHECK_EQ(primesIter1, primesIter2);

	++ascIter1;
	++crossIter1;
	++primesIter1;
	
	CHECK_NE(ascIter1, ascIter2);
	CHECK_GT(ascIter1, ascIter2);
	CHECK_LT(ascIter2, ascIter1);

	CHECK_NE(crossIter1, crossIter2);
	CHECK_GT(crossIter1, crossIter2);
	CHECK_LT(crossIter2, crossIter1);

	CHECK_NE(primesIter1, primesIter2);
	CHECK_GT(primesIter1, primesIter2);
	CHECK_LT(primesIter2, primesIter1);

	++ascIter2;
	++crossIter2;
	++primesIter2;

	CHECK_EQ(ascIter1, ascIter2);
	CHECK_EQ(crossIter1, crossIter2);
	CHECK_EQ(primesIter1, primesIter2);
}