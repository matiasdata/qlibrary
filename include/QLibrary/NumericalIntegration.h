#pragma once

#include <cmath>
#include <stdexcept>

namespace QLibrary
{
    
template <typename T>
double TrapezoidalRule(double a, double b, unsigned long N, T TheFunction)
{
    double integral = 0;
    double h = (b-a)/static_cast<double>(N);
    double x = a;
    integral += 0.5 * TheFunction(x);
    for(unsigned long i = 1; i < N; i++)
    {
        x += h;
        integral += TheFunction(x);
    }
    x = b;
    integral += 0.5 * TheFunction(x);
    integral *= h;
    return integral;
}

template <typename T>
double SimpsonsRule(double a, double b, unsigned long N, T TheFunction)
{   
    if (N % 2 != 0)
    {
        throw std::invalid_argument("N must be even.");
    }
    double integral = 0;
    double h = (b-a)/static_cast<double>(N);
    double x = a;
    integral += TheFunction(x);
    for(unsigned long i = 1; i < N/2; i++)
    {
        x += 2 * h;
        integral += 4 * TheFunction(x);
        integral += 2 * TheFunction(x-h);
    }
    x = b;
    integral += TheFunction(x);
    integral += 2 * TheFunction(x-h);
    integral *= h/3;
    return integral;
}

} // namespace QLibrary
