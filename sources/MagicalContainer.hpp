#pragma once

#include <vector>

namespace ariel {
    class MagicalContainer{
        private:
        /*
        The private vectors to:
        "Create three custom iterator classes named "AscendingIterator", "SideCrossIterator", and "PrimeIterator"
        that will allow traversal of elements in the MagicalContainer class in ascending order, 
        cross order, and prime numbers only, respectively."
        */
            std::vector<int> TheContainer;
            std::vector<const int*> AscendingIter;
            std::vector<const int*> PrimeIter;
            std::vector<const int*> SideCrossIter;

            bool isPrime(int element);

        public:
            MagicalContainer();
            void addElement(int element);
            void removeElement(int element);
            int size() const;
            
        


        
        class BaseIterator {
            private:
                MagicalContainer* _container;
                std::size_t _position;

            public:
                BaseIterator();
                BaseIterator(MagicalContainer* container, std::size_t position);
                BaseIterator(const BaseIterator& other);
                ~BaseIterator() = default;


                bool operator==(const BaseIterator& other) const;
                bool operator!=(const BaseIterator& other) const;
                bool operator<(const BaseIterator& other) const;
                bool operator>(const BaseIterator& other) const;
                
                int operator*();
        };


        class AscendingIterator : public BaseIterator {

            private:
                MagicalContainer& _container;
                std::size_t _index;
            public:
                AscendingIterator();
                AscendingIterator(MagicalContainer& magical);
                AscendingIterator(const AscendingIterator& ascen_iter_other);
                ~AscendingIterator() = default;

                AscendingIterator& operator=(const AscendingIterator& other);

                AscendingIterator& operator++();

                AscendingIterator begin();
                AscendingIterator end();
        };


        class PrimeIterator : public BaseIterator {
            public:
                PrimeIterator();
                PrimeIterator(MagicalContainer& magical);
                PrimeIterator(const PrimeIterator& prime_iter);
                ~PrimeIterator() = default;

                PrimeIterator& operator=(const PrimeIterator& other);

                PrimeIterator& operator++();

                PrimeIterator begin();
                PrimeIterator end();
        };


        class SideCrossIterator : public BaseIterator {
            public:
                SideCrossIterator();
                SideCrossIterator(const MagicalContainer& magical);
                SideCrossIterator(const SideCrossIterator& side_cross_iter);
                ~SideCrossIterator() = default;

                SideCrossIterator& operator=(const SideCrossIterator& other);

                SideCrossIterator& operator++();

                SideCrossIterator begin();
                SideCrossIterator end();
        };

    };

}

