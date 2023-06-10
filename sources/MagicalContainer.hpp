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
            std::set<int> TheContainer;
            std::vector<const int*> AscendingIter;
            std::vector<const int*> PrimeIter;
            std::vector<const int*> SideCrossIter;

            bool isPrime(int element);

        public:
            MagicalContainer();
            void addElement(int element);
            void removeElement(int element);
            int size() const {return TheContainer.size();}
            
        


        
        

        class AscendingIterator : public InterfaceIterator {

            private:
                MagicalContainer* _container;
                std::size_t _index;
            public:
                AscendingIterator(): _container(nullptr), _index(0){} //inline implement
                AscendingIterator(MagicalContainer& container): AscendingIterator(&container, 0){} //inline implement
                AscendingIterator(const AscendingIterator &ascen_iter_other);
                AscendingIterator (MagicalContainer *container, size_t index): _container(container), _index(index){}//inline implement
                ~AscendingIterator() override = default;

                AscendingIterator &operator=(const AscendingIterator &ascen_iter_other);
                bool operator==(const InterfaceIterator &other) const override;
                bool operator!=(const InterfaceIterator &other) const override;
                bool operator<(const InterfaceIterator &other) const override;
                bool operator>(const InterfaceIterator &other) const override;
                bool operator==(const AscendingIterator &other) const;
                bool operator!=(const AscendingIterator &other) const;
                bool operator<(const AscendingIterator &other) const;
                bool operator>(const AscendingIterator &other) const;
                AscendingIterator& operator++();

                AscendingIterator begin();
                AscendingIterator end();
        };


        class PrimeIterator : public InterfaceIterator {
            private:
                MagicalContainer* _container;
                std::size_t _index;
            public:
                PrimeIterator();//implemented
                PrimeIterator(MagicalContainer& magical);//implemented
                PrimeIterator(const PrimeIterator& prime_iter);//implemented
                PrimeIterator(MagicalContainer *container, size_t index): _container(container), _index(index){} //inline implement
                ~PrimeIterator() override = default;

                PrimeIterator &operator=(const PrimeIterator &prime_iter_other);
                bool operator==(const InterfaceIterator &other) const override;
                bool operator!=(const InterfaceIterator &other) const override;
                bool operator<(const InterfaceIterator &other) const override;
                bool operator>(const InterfaceIterator &other) const override;
                bool operator==(const PrimeIterator &other) const;
                bool operator!=(const PrimeIterator &other) const;
                bool operator<(const PrimeIterator &other) const;
                bool operator>(const PrimeIterator &other) const; //implemented
                PrimeIterator& operator++();//implemented

                PrimeIterator begin();
                PrimeIterator end();
        };


        class SideCrossIterator : public InterfaceIterator {
            private:
                MagicalContainer* _container;
                std::size_t _index;
            public:
                SideCrossIterator();
                SideCrossIterator(const MagicalContainer& magical);
                SideCrossIterator(const SideCrossIterator& side_cross_iter);
                SideCrossIterator(MagicalContainer *container, size_t index): _container(container), _index(index){} //inline implement
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

                SideCrossIterator begin();
                SideCrossIterator end();
        };

    };

}

