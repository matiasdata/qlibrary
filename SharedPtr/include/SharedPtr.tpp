#include <SharedPtr.h>

//default constructor
template <typename T>
SharedPtr<T>::SharedPtr() : inner{nullptr}, refCount{new unsigned long(0)} {} 

// constructor from pointer.
template<typename T>
SharedPtr<T>::SharedPtr(T* inner_) : inner{inner_}, refCount{new unsigned long(1)} {} 

// copy constructor
template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
    inner = other.inner; // share the inner pointer.
    refCount = other.refCount;
    if(other.inner != nullptr) // check if other.inner is null
    {
        (*refCount)++; // if the pointer is not null, increment the counter.
    }

} 

template <typename T>
SharedPtr<T>::SharedPtr(const T& inner_)
{
    inner = new T(inner_); // constructor with inner object, inner object shared with the reference count
    if (inner == nullptr) // check if inner is null
    {
        refCount = 0; // set reference count to 0
    }
    else
    {
        refCount = new unsigned long(1); // initialize the reference count to 1
    }
}


template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    if (this != &other) // self-assignment check
    {
        release(); // Properly release the current resource
        inner = other.inner; // copy the new inner object
        refCount = other.refCount; // copy the reference count
        if (other.inner != nullptr) // check if other.inner is null
        {
            (*refCount)++; // increment the reference count
        }        
    }
    return *this; // return the current object
}

template <typename T>
T& SharedPtr<T>::operator*()
{
    return *inner; // dereference operator
}

template <typename T>
const T& SharedPtr<T>::operator*() const
{
    return *inner; // const dereference operator
}

template <typename T>
T* SharedPtr<T>::operator->()
{
    return inner; // pointer operator
}

template <typename T>
const T* const SharedPtr<T>::operator->() const
{
    return inner; // const pointer operator
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    release(); // call the release function to clean up the inner object
    // No need to delete inner or refCount here, as they are handled in release()
    // and the destructor of SharedPtr will be called automatically
    // when the reference count reaches zero.
}
// Destructor to clean up the inner object

template <typename T>
void SharedPtr<T>::release()
{
    (*refCount)--;
    if(*refCount == 0)
    {
        if(inner != nullptr)
        {
            delete inner;
        }
        delete refCount;
    }
}

