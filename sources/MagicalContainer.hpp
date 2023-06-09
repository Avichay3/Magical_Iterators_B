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
            int size() const;
            
        


        
        

        class AscendingIterator : public InterfaceIterator {

            private:
                MagicalContainer* _container;
                std::size_t _index;
            public:
                AscendingIterator();
                AscendingIterator(MagicalContainer& magical);
                AscendingIterator(const AscendingIterator &ascen_iter_other);
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
                PrimeIterator();
                PrimeIterator(MagicalContainer& magical);
                PrimeIterator(const PrimeIterator& prime_iter);
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

