// MyArray.h
#pragma once
#include <valarray>

namespace QLibrary{

class MyArray
{
public:
    explicit MyArray(unsigned long size = 0); // explicit keyword prevents implicit conversions from happening when constructing a MyArray.
    MyArray(const MyArray& other);
    ~MyArray();

    MyArray& operator=(const MyArray& other);
    MyArray& operator=(const double& val);
    MyArray& operator+=(const MyArray& other);
    MyArray& operator-=(const MyArray& other);
    MyArray& operator*=(const MyArray& other);
    MyArray& operator/=(const MyArray& other);
    MyArray& operator+=(const double& val);
    MyArray& operator-=(const double& val);
    MyArray& operator*=(const double& val);
    MyArray& operator/=(const double& val);
    MyArray apply(double f(double)) const;
    inline double operator[](unsigned long i) const; 
    inline double& operator[](unsigned long i);
    inline unsigned long size() const;
    void resize(unsigned long newSize);
    double sum() const;
    double min() const;
    double max() const;
private:
    double* ValuesPtr;
    double* EndPtr;
    unsigned long Size;
    unsigned long Capacity;
};

inline double MyArray::operator[](unsigned long i) const {
    if (i >= Size) {
        throw std::out_of_range("Index out of bounds ");
    }
    return ValuesPtr[i];
}

inline double& MyArray::operator[](unsigned long i) {
    if (i >= Size) {
        throw std::out_of_range("Index out of bounds ");
    }
    return ValuesPtr[i];
}

inline unsigned long MyArray::size() const {
    return Size;
}

}
/* inline: definition must be visible in the same translation unit (e.g. in the header file in this case).
To allow short, performance-critical methods (like operator[]) to be expanded directly — potentially making them faster.
*/
