// Wrapper.h
#pragma once

namespace QLibrary{
    
template <typename T>
class Wrapper
{
public:
    Wrapper(); //default constructor
    Wrapper(const T& inner_); // constructor with inner object
    Wrapper(T* inner_); // constructor with pointer
    Wrapper(const Wrapper<T>& other); // copy constructor
    Wrapper<T>& operator=(const Wrapper<T>& other); // assignment operator
    T& operator*(); // dereference operator
    const T& operator*() const; // const dereference operator
    T* operator->(); // pointer operator
    const T* const operator->() const; // const pointer operator
    ~Wrapper(); // destructor
private:
    T* inner; // pointer to the inner object
};

}
#include <QLibrary/Wrapper.tpp>