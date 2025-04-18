// UniquePtr.h
#pragma once

template <typename T>
class UniquePtr
{
public:
    UniquePtr(); // default constructor
    UniquePtr(const T& inner_); // constructor with inner object reference.
    UniquePtr(T* inner_); // constructor from a pointer.
    UniquePtr(const UniquePtr<T>& other) = delete; // remove copy constructor semantics. 
    // With a delete you can disallow any functionality of a class.
    UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete; // delete (copy) assignment operator
    UniquePtr(UniquePtr<T>&& other); // move constructor
    UniquePtr<T>& operator=(UniquePtr<T>&& other); // move assignment
    T& operator*(); // dereference operator
    const T& operator*() const; // const dereference operator
    T* operator->(); // pointer operator
    const T* const operator->() const; // const pointer operator
    ~UniquePtr(); // destructor
private:
    T* inner;
    void release();
};

#include <QLibrary/UniquePtr.tpp>