// NewtonRaphson.h
#pragma once
#include <cmath>
#include <stdexcept>

namespace QLibrary{
    
template <typename T, double (T::*Value)(double) const, double (T::*Derivative)(double) const>
double NewtonRaphson(double Target, double Start, double Tolerance, const T& TheObject)
{
    if (Tolerance <= 0.0)
    {
        throw std::invalid_argument("Bisection: Tolerance must be positive.");
    }

    double y = (TheObject.*Value)(Start);
    double x = Start;

    static const int MAX_ITER = 1000;
    int iter = 0;
    while ((std::abs(y-Target) > Tolerance) && (iter < MAX_ITER))
    {
        double d = (TheObject.*Derivative)(x);

        x += (Target-y)/d;
        
        y = (TheObject.*Value)(x);
    }
    if (iter >= MAX_ITER)
    {
        std::cerr << "Warning: Bisection reached max iterations (" << MAX_ITER << "). Result may not meet desired tolerance.\n";
    }

    return x;
}

template <typename T, typename Q>
double NewtonRaphsonModern(double Target, double Start, double Tolerance, const T& f, const Q& df)
{
    if (Tolerance <= 0.0)
    {
        throw std::invalid_argument("Bisection: Tolerance must be positive.");
    }

    double y = f(Start);
    double x = Start;

    static const int MAX_ITER = 1000;
    int iter = 0;
    while ((std::abs(y-Target) > Tolerance) && (iter < MAX_ITER))
    {
        double d = df(x);

        x += (Target-y)/d;
        
        y = f(x);
    }
    if (iter >= MAX_ITER)
    {
        std::cerr << "Warning: Bisection reached max iterations (" << MAX_ITER << "). Result may not meet desired tolerance.\n";
    }

    return x;
}

} // namespace QLibrary