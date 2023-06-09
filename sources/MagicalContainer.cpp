#include "MagicalContainer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace ariel;



bool MagicalContainer::isPrime(int element){
    if(element <= 1){ return false; }
    for(int i=2; i < element; i++){
        if(element % i == 0){
            return false;
        }
    }
    return true;
}


MagicalContainer::MagicalContainer(){}

void MagicalContainer::addElement(int element) {
    TheContainer.insert(element);
    // Handle ascending order
    std::sort(AscendingIter.begin(), AscendingIter.end(), [](int a, int b) {
        return a < b;
    });
    // Handle prime order
    if (isPrime(element)) {
        std::sort(PrimeIter.begin(), PrimeIter.end(), [](int a, int b) {
            return a < b;
        });
    }
    // Handle sidecross order 
    SideCrossIter.clear();
    size_t start = 0;
    size_t end = SideCrossIter.size() - 1;
    while (start <= end && end != 0) {
        SideCrossIter.push_back(SideCrossIter[start]);
        if (start != end) {
            SideCrossIter.push_back(SideCrossIter[end]);
        }
        start++;
        end--;
    }
}




void MagicalContainer::removeElement(int element) {
    auto it = TheContainer.find(element);
    if (it == TheContainer.end()){
        throw std::runtime_error("The element was not found");
    }
    //Addressing prime order 
    if (isPrime(element)) {
        auto it_prime = std::find(PrimeIter.begin(), PrimeIter.end(), &(*it));
        if (it_prime != PrimeIter.end()){
            PrimeIter.erase(it_prime);
        }    
    }
    // Addressing ascending order 
    auto iter_ascending = std::find(AscendingIter.begin(), AscendingIter.end(), &(*it));
    if (iter_ascending != AscendingIter.end()){
        AscendingIter.erase(iter_ascending);
    }
    TheContainer.erase(it); // Delete the element --> O(log n)
    SideCrossIter.clear(); // Addressing sidecross order 
    if(size() == 0){ // If the main container is empty, we don't need to rebuild the vector.
    }    return;
    SideCrossIter.reserve(TheContainer.size());
    if(size() == 1){
        SideCrossIter.push_back(AscendingIter[0]);
    }    
    else{
        size_t start = 0, end = (size() - 1);
        while (start <= end && end != 0) {
            SideCrossIter.push_back(AscendingIter[start]);
            if (start != end){
                SideCrossIter.push_back(AscendingIter[end]);
            }
            start++;
            end--;
        }
    }
}






//PrimeIterator class
MagicalContainer::PrimeIterator::PrimeIterator() : _container(nullptr), _index(0){}
    
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& magical){}

//copy constuctor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& prime_iter_other){
    if(_container != prime_iter_other._container && _container != nullptr && prime_iter_other._container != nullptr){
		throw runtime_error("Cannot copy iterators from different containers");
    }    
	_container = prime_iter_other._container;
	_index = prime_iter_other._index;
}    

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &prime_iter_other){
    if (this != &prime_iter_other) {
        _container = prime_iter_other._container;
        _index = prime_iter_other._index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &prime_iter_other) const{
    if(_container != prime_iter_other._container){
		throw runtime_error("Can't compare iterators from different containers");
    }
	if(_container == nullptr || prime_iter_other._container == nullptr){
		throw runtime_error("One of the iterators have not been initialized");
    }
	return _index > prime_iter_other._index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &prime_iter_other) const{
    if(_container != prime_iter_other._container){
		throw runtime_error("Can't compare iterators from different containers");
    }
	if(_container == nullptr || prime_iter_other._container == nullptr){
		throw runtime_error("One of the iterators have not been initialized");
    }
	return _index < prime_iter_other._index;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++(){
    if (_container == nullptr){
		throw runtime_error("Iterator not initialized");
    }
	else if (_index >= _container->PrimeIter.size()){
		throw runtime_error("Iterator out of range");
    }    
	++_index;
	return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){
    return (*this);
}
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
    return (*this);
}




//AscendingIterator class


MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& ascen_iter_other): 
         _container(ascen_iter_other._container), _index(ascen_iter_other._index){
            if (&_container != &ascen_iter_other._container){
		        throw std::runtime_error("can't copy iterators from a different containers");
            }    
}


MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other){
        if (this != &other){
		    if (&_container != &other._container)
			    throw std::runtime_error("can't assign 2 iterators from a different containers");

		    _index = other._index;
        }
	    return *this;
}
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){return (*this);}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){return (*this);}
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
    return (*this);
}





//SideCrossIterator class
MagicalContainer::SideCrossIterator::SideCrossIterator(){}
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& magical){}
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& base_iter){}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other){
    return (*this);
}
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++(){
    return (*this);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){
    return (*this);
}
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){
    return (*this);
}