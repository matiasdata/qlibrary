#include <Wrapper.h>

template <typename T>
Wrapper<T>::Wrapper() : inner{nullptr} {} //default constructor

template <typename T>
Wrapper<T>::Wrapper(const T& inner_)
{
    inner = inner_.clone(); // constructor with inner object using clone.
}

template <typename T>
Wrapper<T>::Wrapper(const Wrapper<T>& other)
{   
    if(other.inner != nullptr) // check if the other inner is null
    {
        inner = other.inner->clone(); // copy constructor using clone.
    }
    else
    {
        inner = nullptr; // if other is null, set inner to null
    }
}

template <typename T>
Wrapper<T>& Wrapper<T>::operator=(const Wrapper<T>& other)
{
    if (this != &other) // self-assignment check
    {
        delete inner; // delete the current inner object
        if (other.inner != nullptr) // check if the other inner is null
        {
            inner = other.inner->clone(); // clone the new inner object
        }
        else
        {
            inner = nullptr; // if other is null, set inner to null
        }
        
    }
    return *this; // return the current object
}

template <typename T>
T& Wrapper<T>::operator*()
{
    return *inner; // dereference operator
}

template <typename T>
const T& Wrapper<T>::operator*() const
{
    return *inner; // const dereference operator
}

template <typename T>
T* Wrapper<T>::operator->()
{
    return inner; // pointer operator
}

template <typename T>
const T* const Wrapper<T>::operator->() const
{
    return inner; // const pointer operator
}

template <typename T>
Wrapper<T>::~Wrapper()
{
    if (inner != nullptr) // check if inner is not null
    {
        delete inner; // delete the inner object
    }
}
// Destructor to clean up the inner object
