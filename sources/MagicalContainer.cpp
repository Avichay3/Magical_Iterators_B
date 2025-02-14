#include "MagicalContainer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <stdexcept>
using namespace std;
using namespace ariel;


//check if a given integer is prime number.
bool MagicalContainer::isPrime(int element){
    if(element <= 1){ return false; }
    for(int i=2; i < element; i++){
        if(element % i == 0){
            return false;
        }
    }
    return true;
}


void MagicalContainer::addElement(int element) {
	auto in = TheContainer.insert(element);
	if (in.second){
		// handle prime order, in this case, we need to find the correct place to insert the element.
		if (isPrime(element)){
			//find the appropriate position to insert the element in the PrimeIter vector using lower_bound which
			//find the first position where a given value can be inserted while maintaining the sorted order.
			//this function take 4 parameters:
			//  1) first element pointer.
			//  2) end element pointer.
			//	3) pointer to the element that should be inserted.
			//  4) lambda function to determine the position of the element
			auto index_to_insert = lower_bound(PrimeIter.begin(), PrimeIter.end(), &(*in.first), [](const int *a, const int *b) {
				return *a < *b;
			});
			PrimeIter.insert(index_to_insert, &(*in.first)); //insert the element at the index we want
		}

		// handle ascending order,in this case, we need to find the correct place to insert the element.
		auto index_to_insert = lower_bound(AscendingIter.begin(), AscendingIter.end(), &(*in.first), [](const int *a, const int *b) {
			return *a < *b;
		});
		AscendingIter.insert(index_to_insert, &(*in.first)); //insert the element at the index we want
		// handle sidecross order,in this case, we need to rebuild the vector.
		SideCrossIter.clear(); // remove all the elements
		// if that's the case, it means there is no need to perform any additional steps to build the side cross iterator
		// the single element from the side cross is added directly using push back
		if (size() == 1){ 
			SideCrossIter.push_back(AscendingIter.front());
		}

		else{ //rebuild the vector
			size_t start = 0;
			size_t end = (size() - 1);
			while (start <= end && end != 0){ //ensures that the loop terminates when the indices meet in the middle
				SideCrossIter.push_back(AscendingIter.at(start));
				if (start != end){
					SideCrossIter.push_back(AscendingIter.at(end));
				}
				start++;
				end--;
			}
		}
	}
}





void MagicalContainer::removeElement(int element) {
	auto it = TheContainer.find(element);

	if (it == TheContainer.end()){
		throw std::runtime_error("Element not found");
	}
	// handle prime order, in this case, we need to find the element in the vector to remove it.
	if (isPrime(element)){
		auto it_prime = find(PrimeIter.begin(), PrimeIter.end(), &(*it));
		PrimeIter.erase(it_prime);
	}

	// handle ascending order - O(n) in this case, as we need to find the element in the vector to remove it.
	auto it_ascending = find(AscendingIter.begin(), AscendingIter.end(), &(*it));
	AscendingIter.erase(it_ascending);

	// delete the element 
	TheContainer.erase(element);

	// handle sidecross order,in this case, as we need to rebuild the vector.
	SideCrossIter.clear();

	// Incase the main container is empty, we don't need to rebuild the vector.
	if (size() == 0)
		return;

	SideCrossIter.reserve(TheContainer.size());

	if (size() == 1){
		SideCrossIter.push_back(AscendingIter.at(0));
	}
	else{
		size_t start = 0, end = (size_t)(size() - 1);
		while (start <= end && end != 0){
			SideCrossIter.push_back(AscendingIter.at(start));

			if (start != end){
				SideCrossIter.push_back(AscendingIter.at(end));
			}
			start++;
			end--;
		}
	}
}




//AscendingIterator class
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& ascen_iter_other): 
         _container(ascen_iter_other._container), _index(ascen_iter_other._index){
            if (&_container != &ascen_iter_other._container){
		        throw std::runtime_error("can't copy iterators from a different containers");
            }    
}


MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator &ascen_iter_other){
        if (this != &ascen_iter_other){
		    if (&_container != &ascen_iter_other._container){
			    throw std::runtime_error("can't assign 2 iterators from a different containers");
            }
		    _index = ascen_iter_other._index;
        }
	    return *this;
}


bool MagicalContainer::AscendingIterator::operator==(const InterfaceIterator &other) const{
	auto other_ptr = dynamic_cast<const AscendingIterator *>(&other);
	if (other_ptr == nullptr){
		throw std::runtime_error("Cannot compare iterators of different types");
    }
	if (_container == nullptr || other_ptr->_container == nullptr){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	if (_container != other_ptr->_container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index == other_ptr->_index;
}


bool MagicalContainer::AscendingIterator::operator!=(const InterfaceIterator &other) const {
	const AscendingIterator *other_ptr = dynamic_cast<const AscendingIterator *>(&other);
	if (other_ptr == nullptr){
		throw runtime_error("Cannot compare iterators of different types");
    }
	else if(_container == nullptr || other_ptr->_container == nullptr){
		throw runtime_error("One of the iterators is not initialized");
    }
	else if(_container != other_ptr->_container){
		throw runtime_error("Cannot compare iterators from different containers");
    }
	return _index != other_ptr->_index;
}


bool MagicalContainer::AscendingIterator::operator<(const InterfaceIterator &other) const {
	auto other_ptr = dynamic_cast<const AscendingIterator *>(&other);
	if(other_ptr == nullptr){
		throw std::runtime_error("Cannot compare iterators of different types");
    }
	if(!_container || !(other_ptr->_container)){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	if(_container != other_ptr->_container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index < other_ptr->_index;
}


bool MagicalContainer::AscendingIterator::operator>(const InterfaceIterator &other) const {
	auto other_ptr = dynamic_cast<const AscendingIterator *>(&other);
	if(other_ptr == nullptr){
		throw std::runtime_error("Cannot compare iterators of different types");
    }
	if(!_container || !(other_ptr->_container)){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	if(_container != other_ptr->_container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index > other_ptr->_index;
}


bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
	// Check if either iterator is not initialized
	if (!_container || !(other._container)){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	// Check if iterators belong to different containers
	if (_container != other._container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	// Compare the index values
	return _index == other._index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
	// Check if either iterator is not initialized
	if (!_container || !(other._container)){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	// Check if iterators belong to different containers
	if (_container != other._container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	// Compare the index values
	return _index != other._index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    // Check if either iterator is not initialized
    if (!_container || !other._container){
        throw std::runtime_error("One of the iterators is not initialized");
    }
    // Check if iterators belong to different containers
    if (_container != other._container){
        throw std::runtime_error("Cannot compare iterators from different containers");
    }
    // Compare the index values
    return _index < other._index;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    // Check if either iterator is not initialized
    if (!_container || !other._container){
        throw std::runtime_error("One of the iterators is not initialized");
    }
    // Check if iterators belong to different containers
    if (_container != other._container){
        throw std::runtime_error("Cannot compare iterators from different containers");
    }
    // Compare the index values
    return _index > other._index;
}



MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    // Check if the iterator is not initialized
    if (_container == nullptr){
        throw std::runtime_error("Iterator not initialized");
    }
    // Check if the iterator is out of range
    if (_index >= _container->SideCrossIter.size()){
        throw std::runtime_error("Iterator out of range");
    }
    // Increment the index
    ++_index;
    // Return a reference to the updated iterator
    return *this;
}


int MagicalContainer::AscendingIterator::operator*() const {
	if (_container == nullptr){
		throw std::runtime_error("Iterator not initialized");
    }
	else if (_index >= _container->AscendingIter.size()){
		throw std::runtime_error("Iterator out of range");
    }
	return *(_container->AscendingIter.at(_index));
}














//Prime Iterator class
MagicalContainer::PrimeIterator::PrimeIterator() : _container(nullptr), _index(0){}
    

//copy constuctor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& prime_iter_other){
    if(_container != prime_iter_other._container && _container != nullptr && prime_iter_other._container != nullptr){
		throw std::runtime_error("Cannot copy iterators from different containers");
    }    
	_container = prime_iter_other._container;
	_index = prime_iter_other._index;
}    



bool MagicalContainer::PrimeIterator::operator==(const InterfaceIterator &other) const{
	const PrimeIterator *other_ptr = dynamic_cast<const PrimeIterator *>(&other);
	if(other_ptr == nullptr){
		throw runtime_error("Cannot compare iterators of different types");
    }
	else if (_container == nullptr || other_ptr->_container == nullptr){
		throw runtime_error("One of the iterators is not initialized");
    }
	else if (_container != other_ptr->_container){
		throw runtime_error("Cannot compare iterators from different containers");
    }
	return _index == other_ptr->_index;
}




bool MagicalContainer::PrimeIterator::operator<(const InterfaceIterator &Inter_iter_other) const {
	const PrimeIterator *ptr_other = dynamic_cast<const PrimeIterator *>(&Inter_iter_other);
    if(_container == nullptr || ptr_other->_container == nullptr){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	if(ptr_other == nullptr){
		throw std::runtime_error("Cannot compare iterators of different types");
    }
	else if(_container != ptr_other->_container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index < ptr_other->_index;
}


bool MagicalContainer::PrimeIterator::operator>(const InterfaceIterator &Inter_iter_other) const {
	const PrimeIterator *ptr_other = dynamic_cast<const PrimeIterator *>(&Inter_iter_other);
    if(_container == nullptr || ptr_other->_container == nullptr){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	if(ptr_other == nullptr){
		throw std::runtime_error("Cannot compare iterators of different types");
    }
	else if(_container != ptr_other->_container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index > ptr_other->_index;
}



bool MagicalContainer::PrimeIterator::operator!=(const InterfaceIterator& Inter_iter_other) const{
    try{
        const PrimeIterator& otherPrimeIter = dynamic_cast<const PrimeIterator&>(Inter_iter_other);
        if(_container == nullptr) {
            if (otherPrimeIter._container == nullptr){
                throw std::runtime_error("Both iterators have not initialized");
            }
            else
                throw std::runtime_error("The current iterator has not initialized");
        }else if (otherPrimeIter._container == nullptr){
            throw std::runtime_error("The other iterator is not initialized");
        }
        if (_container != otherPrimeIter._container)
            throw std::runtime_error("Can't compare iterators from different containers");

        return (_index != otherPrimeIter._index);
    } 
    catch (const std::bad_cast&){  // catch case where cast is not good
        throw std::runtime_error("Can't compare iterators of different types");
    }
}



MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
	if (this != &other){
		if (_container != other._container && _container != nullptr && other._container != nullptr){
			throw std::runtime_error("Cannot assign iterators from different containers");
		}
		_container = other._container;
		_index = other._index;
	}
	return *this;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &prime_iter_other) const{
    if(_container != prime_iter_other._container){
		throw std::runtime_error("Can't compare iterators from different containers");
    }
	if(_container == nullptr || prime_iter_other._container == nullptr){
		throw std::runtime_error("One of the iterators have not been initialized");
    }
	return _index > prime_iter_other._index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &prime_iter_other) const{
    if(_container != prime_iter_other._container){
		throw std::runtime_error("Can't compare iterators from different containers");
    }
	if(_container == nullptr || prime_iter_other._container == nullptr){
		throw std::runtime_error("One of the iterators have not been initialized");
    }
	return _index < prime_iter_other._index;
}


bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
	if (_container == nullptr){
		throw std::runtime_error("Iterator not initialized");
    }
	else if (_container != other._container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index == other._index;
}


MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++(){
    if (_container == nullptr){
		throw std::runtime_error("Iterator not initialized");
    }
	else if (_index >= _container->PrimeIter.size()){
		throw std::runtime_error("Iterator out of range");
    }    
	++_index;
	return *this;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& prime_iter_other) const{
    if (!_container){
        if (prime_iter_other._container == nullptr){
            throw std::runtime_error("Both iterators are not initialized");
        }    
        else{
            throw std::runtime_error("Current iterator is not initialized");
        }
    }else if (prime_iter_other._container == nullptr) {
        throw std::runtime_error("Other iterator is not initialized");
    }

    if (_container != prime_iter_other._container)
        throw std::runtime_error("Cannot compare iterators from different containers");
    return (_index != prime_iter_other._index);
}


int MagicalContainer::PrimeIterator::operator*() const{
	if (_container == nullptr){
		throw std::runtime_error("Iterator not initialized");
    }
	else if (_index >= _container->PrimeIter.size()){
		throw runtime_error("Iterator out of range");
    }
	return *(_container->PrimeIter.at(_index));
}














// Side Cross Iterator class
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &side_cross_iter_other) {
	if (_container != side_cross_iter_other._container && _container != nullptr && side_cross_iter_other._container != nullptr){
		throw runtime_error("Cannot copy iterators from different containers");
    }
	_container = side_cross_iter_other._container;
	_index = side_cross_iter_other._index;
}



MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
	if (this != &other){
		if (&_container != &other._container){
			throw runtime_error("Cannot assign iterators from different containers");
        }
		_index = other._index;
	}
	return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const InterfaceIterator &other) const{
	const SideCrossIterator *other_ptr = dynamic_cast<const SideCrossIterator *>(&other);
	if (other_ptr == nullptr){
		throw runtime_error("Cannot compare iterators of different types");
    }
	else if (_container == nullptr || other_ptr->_container == nullptr){
		throw runtime_error("One of the iterators is not initialized");
    }
	else if (_container != other_ptr->_container){
		throw runtime_error("Cannot compare iterators from different containers");
    }
	return _index == other_ptr->_index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const InterfaceIterator &other) const{
	const SideCrossIterator *other_ptr = dynamic_cast<const SideCrossIterator *>(&other);
	if (other_ptr == nullptr){
		throw runtime_error("Cannot compare iterators of different types");
    }
	else if (_container == nullptr || other_ptr->_container == nullptr){
		throw std::runtime_error("One of the iterators is not initialized");
    }
	else if (_container != other_ptr->_container){
		throw std::runtime_error("Cannot compare iterators from different containers");
    }
	return _index != other_ptr->_index;
}

bool MagicalContainer::SideCrossIterator::operator<(const InterfaceIterator &other) const{
	const SideCrossIterator *other_ptr = dynamic_cast<const SideCrossIterator *>(&other);
	if (other_ptr == nullptr){
		throw runtime_error("Cannot compare iterators of different types");
    }
	else if (_container == nullptr || other_ptr->_container == nullptr){
		throw runtime_error("One of the iterators is not initialized");
    }
	else if (_container != other_ptr->_container){
		throw runtime_error("Cannot compare iterators from different containers");
    }
	return _index < other_ptr->_index;
}

bool MagicalContainer::SideCrossIterator::operator>(const InterfaceIterator &other) const{
	const SideCrossIterator *other_ptr = dynamic_cast<const SideCrossIterator *>(&other);
	if (other_ptr == nullptr){
		throw runtime_error("Cannot compare iterators of different types");
    }
	else if (_container == nullptr || other_ptr->_container == nullptr){
		throw runtime_error("One of the iterators is not initialized");
    }
	else if (_container != other_ptr->_container){
		throw runtime_error("Cannot compare iterators from different containers");
    }
	return _index > other_ptr->_index;
}


bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const{
    // Check if either iterator is not initialized
    if (_container == nullptr || other._container == nullptr){
        throw std::runtime_error("One of the iterators is not initialized");
    }
    // Check if iterators belong to different containers
    if (_container != other._container){
        throw std::runtime_error("Cannot compare iterators from different containers");
    }
    // Compare the index values
    return _index == other._index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const{
    // Check if either iterator is not initialized
    if (_container == nullptr || other._container == nullptr){
        throw std::runtime_error("One of the iterators is not initialized");
    }
    // Check if iterators belong to different containers
    if (_container != other._container){
        throw std::runtime_error("Cannot compare iterators from different containers");
    }
    // Compare the index values
    return _index != other._index;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    // Check if either iterator is not initialized
    if (_container == nullptr || other._container == nullptr){
        throw std::runtime_error("One of the iterators is not initialized");
    }
    // Check if iterators belong to different containers
    if (_container != other._container){
        throw std::runtime_error("Cannot compare iterators from different containers");
    }
    // Compare the index values
    return _index < other._index;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    // Check if either iterator is not initialized
    if (_container == nullptr || other._container == nullptr){
        throw std::runtime_error("One of the iterators is not initialized");
    }
    // Check if iterators belong to different containers
    if (_container != other._container){
        throw std::runtime_error("Cannot compare iterators from different containers");
    }
    // Compare the index values
    return _index > other._index;
}


MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
	if(_container == nullptr){
		throw std::runtime_error("Iterator not initialized");
    }
	else if(_index >= _container->SideCrossIter.size()){
		throw std::runtime_error("Iterator out of range");
    }
	++_index;
	return *this;
}


int MagicalContainer::SideCrossIterator::operator*() const{
	if (_container == nullptr){
		throw std::runtime_error("Iterator not initialized");
    }
	else if (_index >= _container->AscendingIter.size()){
		throw std::runtime_error("Iterator out of range");
    }
	return *(_container->SideCrossIter.at(_index));
}











