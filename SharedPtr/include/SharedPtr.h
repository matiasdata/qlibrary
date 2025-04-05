#pragma once

template <typename T>
class SharedPtr
{
public:
    SharedPtr(); //default constructor
    SharedPtr(const T& inner_); // constructor with inner object reference.
    SharedPtr(T* inner_); // constructor from pointer.
    SharedPtr(const SharedPtr<T>& other); // copy constructor
    SharedPtr<T>& operator=(const SharedPtr<T>& other); // assignment operator
    T& operator*(); // dereference operator
    const T& operator*() const; // const dereference operator
    T* operator->(); // pointer operator
    const T* const operator->() const; // const pointer operator
    unsigned long getRefCount() const { return *refCount; } // get reference count
    ~SharedPtr(); // destructor

private:
    T* inner; // pointer to the inner object
    unsigned long* refCount; // reference count
    void release(); // release the inner object and decrement the reference count
};

#include <SharedPtr.tpp>