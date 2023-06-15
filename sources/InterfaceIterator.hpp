#pragma once

namespace ariel{

    class InterfaceIterator{
    private:
        /* There is no private data because this is an "interface" for the iterators*/

    public:
    /*defines the common methods and operators that all iterators derived from this class should implement.*/
        InterfaceIterator() = default;

        //set to default, meaning the compiler will generate the destructor implementation
        virtual ~InterfaceIterator() = default;

        //a copy constructor. set to default, indicating that the compiler will generate the copy constructor implementation.
        InterfaceIterator(const InterfaceIterator &other) = default; 

        //copy assignment operator
        InterfaceIterator& operator=(const InterfaceIterator &other) = default; 

        //pure virtual function(means that the function must be overridden) that represents the equality comparison operator.
        //compares the current iterator instance with another iterator instance and
        // returns a boolean value indicating whether they are equal.
        virtual bool operator==(const InterfaceIterator &other) const = 0;

        //pure virtual function(means that the function must be overridden) that represents the inequality comparison operator.
        //compares the current iterator instance with another iterator instance and
        // returns a boolean value indicating whether they are not equal.
        virtual bool operator!=(const InterfaceIterator &other) const = 0;

        //pure virtual function(means that the function must be overridden) that represents the greater than comparison operator.
        //compares the current iterator instance with another iterator instance and
        // returns a boolean value indicating whether the current iterator is greater than the other.
        virtual bool operator>(const InterfaceIterator &other) const = 0;

        //pure virtual function(means that the function must be overridden) that represents the less than comparison operator.
        //compares the current iterator instance with another iterator instance and
        // returns a boolean value indicating whether the current iterator is less than the other.
        virtual bool operator<(const InterfaceIterator &other) const = 0;

    };
    
    
    





}
