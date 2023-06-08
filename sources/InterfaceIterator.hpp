#pragma once

namespace arie{

    class InterfaceIterator{
    private:
        /* There is no private data because this is an interface for the iterators*/
    public:
        InterfaceIterator() = default;
        virtual ~InterfaceIterator() = default;
        InterfaceIterator(const InterfaceIterator &other) = default; // means that all parameters have default values 


        InterfaceIterator& operator=(const InterfaceIterator &other) = default;
        virtual bool operator==(const InterfaceIterator &other) const = 0;
        virtual bool operator!=(const InterfaceIterator &other) const = 0;
        virtual bool operator>(const InterfaceIterator &other) const = 0;
        virtual bool operator<(const InterfaceIterator &other) const = 0;

    };
    
    
    





}
