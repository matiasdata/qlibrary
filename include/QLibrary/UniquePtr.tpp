#include <QLibrary/UniquePtr.h>


template<typename T>
UniquePtr<T>::UniquePtr() : inner{nullptr} {} // default constructor

template<typename T>
UniquePtr<T>::UniquePtr(const T& inner_) : inner{new T(inner_)} {} // constructor from inner object reference.

template<typename T>
UniquePtr<T>::UniquePtr(T* inner_) : inner{inner_} {} // constructor from a pointer.

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other)
{
    inner = other.inner;
    other.inner = nullptr;
} // move constructor

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other)
{
    if (this != &other) {
        release();
        inner = other.inner;
        other.inner = nullptr;
    }
    return *this;
}

template<typename T>
T& UniquePtr<T>::operator*()
{
    return *inner;
}

template<typename T>
const T& UniquePtr<T>::operator*() const
{
    return *inner;
}

template<typename T>
T* UniquePtr<T>::operator->()
{
    return inner;
}

template<typename T>
const T* const UniquePtr<T>::operator->() const
{
    return inner;
}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
    release();
}

template<typename T>
void UniquePtr<T>::release()
{
    if (inner != nullptr)
    {
        delete inner;
        inner = nullptr;
    }
}

