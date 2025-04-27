// MyArray.cpp
#include <QLibrary/MyArray.h>
#include <algorithm>
#include <numeric>
#include <stdexcept>

MyArray::MyArray(unsigned long size) : Size{size}, Capacity{size}
{
    if(Size > 0)
    {
        ValuesPtr = new double[size];
        EndPtr = ValuesPtr;
        EndPtr += Size; // pointer arithmetic
    }
    else
    {
        ValuesPtr = nullptr;
        EndPtr = nullptr;
    }
}

// copy constructor
MyArray::MyArray(const MyArray& other) : Size{other.Size}, Capacity{other.Capacity} 
{
    if(Size > 0)
    {
        ValuesPtr = new double[Size];
        EndPtr = ValuesPtr;
        EndPtr += Size;
        std::copy(other.ValuesPtr, other.EndPtr,ValuesPtr); // copy the array using the standard library function.
    }
    else
    {
        ValuesPtr = nullptr;
        EndPtr = nullptr;   
    }
}

MyArray::~MyArray()
{
    if(ValuesPtr != nullptr)
    {
        delete[] ValuesPtr; // delete the array (all allocated memory is returned).
    }
}

MyArray& MyArray::operator=(const MyArray& other)
{
    if(this != &other) // self assignment check
    {
        if(other.Size > Capacity)
        {
            if(Capacity > 0)
            {
                delete[] ValuesPtr;
            }
            ValuesPtr = new double[other.Size];
            Capacity = other.Size;
        }
        Size = other.Size;

        EndPtr = ValuesPtr;
        EndPtr += Size;
        std::copy(other.ValuesPtr, other.EndPtr, ValuesPtr);
    }
    return *this;
}

MyArray& MyArray::operator=(const double& val)
{
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] = val;
    }
    return *this;
}

MyArray& MyArray::operator+=(const MyArray& other)
{
    if(Size != other.Size)
    {
        throw std::invalid_argument("Error, operator+= requires two arrays of the same size.");
    }
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] += other[i];
    }
    return *this;
}

MyArray& MyArray::operator+=(const double& val)
{
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] += val;
    }
    return *this;
}

MyArray& MyArray::operator-=(const MyArray& other)
{
    if(Size != other.Size)
    {
        throw std::invalid_argument("Error, operator-= requires two arrays of the same size.");
    }
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] -= other[i];
    }
    return *this;
}

MyArray& MyArray::operator-=(const double& val)
{
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] -= val;
    }
    return *this;
}

MyArray& MyArray::operator*=(const MyArray& other)
{
    if(Size != other.Size)
    {
        throw std::invalid_argument("Error, operator*= requires two arrays of the same size.");
    }
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] *= other[i];
    }
    return *this;
}

MyArray& MyArray::operator*=(const double& val)
{
    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] *= val;
    }
    return *this;
}

MyArray& MyArray::operator/=(const MyArray& other)
{
    if(Size != other.Size)
    {
        throw std::invalid_argument("Error, operator*= requires two arrays of the same size.");
    }
    for(unsigned long i = 0; i < Size; i++)
    {
        if(other[i] == 0)
        {
            throw std::runtime_error("Error, division by zero.");
        }
        ValuesPtr[i] /= other[i];
    }
    return *this;
}

MyArray& MyArray::operator/=(const double& val)
{
    if(val == 0)
    {
        throw std::runtime_error("Error, division by zero.");
    }

    for(unsigned long i = 0; i < Size; i++)
    {
        ValuesPtr[i] /= val;
    }
    return *this;
}

void MyArray::resize(unsigned long newSize)
{
    if(newSize > Capacity)
    {
        if(Capacity > 0)
        {
            delete[] ValuesPtr;
        }
        ValuesPtr = new double[newSize];
        Capacity = newSize;
    }
    Size = newSize;
    EndPtr = ValuesPtr;
    EndPtr += Size;
} 
// We follow the valarray class in not requiring the resize operation to preserve the underlying data.

double MyArray::sum() const
{
    return std::accumulate(ValuesPtr,EndPtr,0.0);
}

double MyArray::min() const
{
    if(Size == 0)
    {
        throw std::out_of_range("Error, cannot compute min of an empty array.");
    }
    double* tmp = ValuesPtr;
    double* endTmp = EndPtr;

    return *std::min_element(tmp,endTmp);
}

double MyArray::max() const
{
    if(Size == 0)
    {
        throw std::out_of_range("Error, cannot compute max of an empty array.");
    }
    double* tmp = ValuesPtr;
    double* endTmp = EndPtr;

    return *std::max_element(tmp,endTmp);
}

MyArray MyArray::apply(double f(double)) const
{
    MyArray result(size());
    std::transform(ValuesPtr, EndPtr,result.ValuesPtr,f);
    return result;
}