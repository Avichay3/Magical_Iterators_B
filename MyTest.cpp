

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

	mc.addElement(1); //add the element 1.
	CHECK_EQ(mc.size(), 1);//check the size if correct.

	mc.addElement(2);//add.
	mc.addElement(3);//add.

	CHECK_EQ(mc.size(), 3); //check size if correct.

	mc.removeElement(2); //removing element.
	CHECK_EQ(mc.size(), 2); // check size after remove.

	mc.removeElement(1); //removing element.
	mc.removeElement(3); //removing element.

	CHECK_EQ(mc.size(), 0); //check the size if correct.
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
	++ascIter; // point to the next.
	CHECK_EQ(*ascIter, 4); //checking if it pointer now point to 4 after promoting the pointer.
	++ascIter; // point to the next.
	CHECK_EQ(ascIter, ascIter.end());//check if iterator has reached the end.
}

TEST_CASE("Test 3 - Iterator SideCross") {
	MagicalContainer mc; //creating empty instance of MagicalContainer.
	mc.addElement(2); //add 2.
	mc.addElement(4); //add 4.
	mc.addElement(3); // add 3.

	MagicalContainer::SideCrossIterator crossIter(mc); // creating instance of side cross iterator.
    //this iterator return one element from the start and one from the end and so on..

	CHECK_EQ(*crossIter, 2);//checking if the first element returned by the pointer to iterator is 2.
	++crossIter; // point to the next.
	CHECK_EQ(*crossIter, 4);//checking if it pointer now point to 4 after promoting the pointer.
	++crossIter;// point to the next.
	CHECK_EQ(*crossIter, 3);//checking if it pointer now point to 3 after promoting the pointer.
	++crossIter;
	CHECK_EQ(crossIter, crossIter.end());//check if iterator has reached the end.
}

TEST_CASE("Test 4 - Iterator Prime") {
	MagicalContainer mc; //creating empty instance of MagicalContainer.
	mc.addElement(3);//add 3.
	mc.addElement(4);//add 4.
	mc.addElement(2);// add 2.

	MagicalContainer::PrimeIterator primesIter(mc); // creating instance of prime iterator.

	CHECK_EQ(*primesIter, 2);//checking if the first element returned by the pointer to iterator is 2.
	++primesIter; // point to the next.
	CHECK_EQ(*primesIter, 3);
	++primesIter; // point to the next.
	CHECK_EQ(primesIter, primesIter.end()); //check if iterator has reached the end.
}

TEST_CASE("Test 5 - Check iterators comparison") {
	MagicalContainer mc; //creating empty instance of MagicalContainer.
	mc.addElement(3);//add 3.
	mc.addElement(4);//add 4.
	mc.addElement(2);// add 2.

	MagicalContainer::AscendingIterator ascIter1(mc);//creating ascending iterator and initialize with mc
	MagicalContainer::AscendingIterator ascIter2(mc); //creating ascending iterator and initialize with mc
	MagicalContainer::SideCrossIterator crossIter1(mc); //creating sideCross iterator and initialize with mc
	MagicalContainer::SideCrossIterator crossIter2(mc); //creating sideCross iterator and initialize with mc
	MagicalContainer::PrimeIterator primesIter1(mc); //creating prime iterator and initialize with mc
	MagicalContainer::PrimeIterator primesIter2(mc); //creating prime iterator and initialize with mc

	CHECK_EQ(ascIter1, ascIter2); //check if both  instances are initially pointing to the same position in the container.
	CHECK_EQ(crossIter1, crossIter2);  //check if both  instances are initially pointing to the same position in the container.
	CHECK_EQ(primesIter1, primesIter2);  //check if both  instances are initially pointing to the same position in the container.

	++ascIter1; //increment to the next element in ascending.
	++crossIter1; //increment to the next element in sideCross.
	++primesIter1; //increment to the next element in prime.
	
	CHECK_NE(ascIter1, ascIter2); //check if not equal
	CHECK_GT(ascIter1, ascIter2); //check if ascIter1 greater than ascIter2
	CHECK_LT(ascIter2, ascIter1); //check if ascIter2 lower than ascIter1

    /*same thing for the rest lines*/

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
