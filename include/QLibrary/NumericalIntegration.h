// NumericalIntegration.h
#pragma once

#include <cmath>
#include <stdexcept>

namespace QLibrary
{
    
template <typename T>
double TrapezoidalRule(double a, double b, unsigned long N, T TheFunction)
{
    double h = (b-a)/static_cast<double>(N);
    
    double sum = 0.5 * (TheFunction(a) + TheFunction(b));
    double x = a;
    for(unsigned long i = 1; i < N; i++)
    {
        x += h;
        sum += TheFunction(x);
    }
    return sum * h;
}

template <typename T>
double SimpsonsRule(double a, double b, unsigned long N, T TheFunction)
{   
    if (N % 2 != 0)
    {
        throw std::invalid_argument("N must be even.");
    }
    double h = (b - a) / N;
    double sum = TheFunction(a) + TheFunction(b);

    for (unsigned long i = 1; i < N; i++)
    {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2 * TheFunction(x);
        else
            sum += 4 * TheFunction(x);
    }
    return sum * h / 3.0;
}

} // namespace QLibrary
