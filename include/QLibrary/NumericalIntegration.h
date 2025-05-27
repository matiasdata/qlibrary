#pragma once

#include <cmath>

namespace QLibrary
{
    
template <typename T>
double TrapezoidalRule(double a, double b, unsigned long N, T TheFunction)
{
    double integral = 0;
    double deltax = (b-a)/static_cast<double>(N);
    double x = a;
    integral += 0.5 * TheFunction(x);
    for(unsigned long i = 1; i < N; i++)
    {
        x += deltax;
        integral += TheFunction(x);
    }
    x = b;
    integral += 0.5 * TheFunction(x);
    integral *= deltax;
    return integral;
}


} // namespace QLibrary
