#pragma once

#include <vector>
#include <set>
#include "InterfaceIterator.hpp"

namespace ariel {
    class MagicalContainer{
        private:
        /*
        The private vectors to:
        "Create three custom iterator classes named "AscendingIterator", "SideCrossIterator", and "PrimeIterator"
        that will allow traversal of elements in the MagicalContainer class in ascending order, 
        cross order, and prime numbers only, respectively."
        */


            /*Container that stores unique elements(no duplicate values), because this is a set.
              The elements in a set are always sorted in ascending order by default.
              the time complexity for searching an element is logarithmic, O(log n) because 
              this is implemented as a balanced binary search tree.*/
            std::set<int> TheContainer;

            /*Vectors that store pointers to the elements of the container based on specific iterator requirements.*/
            std::vector<const int*> AscendingIter;
            std::vector<const int*> PrimeIter;
            std::vector<const int*> SideCrossIter;

            bool isPrime(int element); //for the prime iterator

        public:
            MagicalContainer(); // default constructor.
            void addElement(int element); // add element method
            void removeElement(int element); // remove element method
            int size() const {return TheContainer.size();} //inline implement for the size
            
        


        
        
        /*now i will create a 3 classes, all inherit from the InterfaceIterator*/

        //represents an iterator that allows traversal of elements in ascending order
        class AscendingIterator : public InterfaceIterator { 

            private:
                MagicalContainer* _container; //pointer to magicalContainer object
                std::size_t _index; //index indicating the current position of the iterator.
            public:
                AscendingIterator(): _container(nullptr), _index(0){} //inline implement
                AscendingIterator(MagicalContainer& container): AscendingIterator(&container, 0){} //inline implement
                AscendingIterator(const AscendingIterator &ascen_iter_other);//copy constructor
                //constructor that takes pointer to magicalContainer and index
                AscendingIterator (MagicalContainer *container, std::size_t index): _container(container), _index(index){}//inline implement
                ~AscendingIterator() override = default; //destructor


                /*operators overloading*/
                AscendingIterator &operator=(const AscendingIterator &ascen_iter_other);

                //compares the current ascending iterator object with another InterfaceIterator
                //overriding a virtual function from the base class 'InterfaceIterator'.
                bool operator==(const InterfaceIterator &other) const override;

                //same thing as before but return the oposite
                bool operator!=(const InterfaceIterator &other) const override;

                //compare the positions of two iterator objects.
                bool operator<(const InterfaceIterator &other) const override;
                bool operator>(const InterfaceIterator &other) const override;

                //compare the current ascending iterator with the other from the same object.
                bool operator==(const AscendingIterator &other) const;
                bool operator!=(const AscendingIterator &other) const;

                //if the current iterator is positioned at an index smaller/greater than the other iterator index.
                bool operator<(const AscendingIterator &other) const;
                bool operator>(const AscendingIterator &other) const;

                //allows accessing the value pointed to by the ascending iterator.
                int operator*() const;

                AscendingIterator& operator++(); //pre increment operator oveload

                //returns a new AscendingIterator object that points to the beginning of the container.
                AscendingIterator begin() {//inline implementation
					return AscendingIterator(_container, 0);
				}

                //returns a new AscendingIterator object that points to the end of the container.
                AscendingIterator end() const { //inline implementation
					return AscendingIterator(_container, _container->AscendingIter.size());
				}
        };



        /*the exact same comments as the previous iterator buut just for the prime iterator*/
        class PrimeIterator : public InterfaceIterator {
            private:
                MagicalContainer* _container;
                std::size_t _index;
            public:
                PrimeIterator();
                PrimeIterator(MagicalContainer &container): _container(&container), _index(0) {}
                PrimeIterator(const PrimeIterator& prime_iter);
                PrimeIterator(MagicalContainer *container, std::size_t index): _container(container), _index(index){} //inline implement
                ~PrimeIterator() override = default;

                PrimeIterator &operator=(const PrimeIterator &prime_iter_other);
                bool operator==(const InterfaceIterator &other) const override;
                bool operator!=(const InterfaceIterator &other) const override;
                bool operator<(const InterfaceIterator &other) const override;
                bool operator>(const InterfaceIterator &other) const override;
                bool operator==(const PrimeIterator &other) const;
                bool operator!=(const PrimeIterator &other) const;
                bool operator<(const PrimeIterator &other) const;
                bool operator>(const PrimeIterator &other) const; 
                PrimeIterator& operator++();
                int operator*() const;

                PrimeIterator begin(){
                    return PrimeIterator(_container, 0);
                }
                PrimeIterator end() const{
                    return PrimeIterator(_container, _container->PrimeIter.size());
                }
        };




        /*the exact same comments as the previous iterator buut just for the side cross iterator*/
        class SideCrossIterator : public InterfaceIterator {
            private:
                MagicalContainer* _container;
                std::size_t _index;
            public:
                SideCrossIterator(): _container(nullptr), _index(0) {}//inline implementation
                SideCrossIterator(MagicalContainer& magical): _container(&magical), _index(0){}//inline implementation
                SideCrossIterator(const SideCrossIterator& side_cross_iter);
                SideCrossIterator(MagicalContainer *container, std::size_t index): _container(container), _index(index){} //inline implement
                ~SideCrossIterator() override = default;

                SideCrossIterator &operator=(const SideCrossIterator &side_cross_iter_other);
                bool operator==(const InterfaceIterator &other) const override;
                bool operator!=(const InterfaceIterator &other) const override;
                bool operator<(const InterfaceIterator &other) const override;
                bool operator>(const InterfaceIterator &other) const override;
                bool operator==(const SideCrossIterator &other) const;
                bool operator!=(const SideCrossIterator &other) const;
                bool operator<(const SideCrossIterator &other) const;
                bool operator>(const SideCrossIterator &other) const;
                SideCrossIterator& operator++();
                int operator*() const;

                SideCrossIterator begin(){
                    return SideCrossIterator(_container, 0);
                }
                SideCrossIterator end() const{
                    return SideCrossIterator(_container, _container->SideCrossIter.size());
                }
        };

    };

}

