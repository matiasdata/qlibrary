// Bisection.h
#include <cmath>
#include <stdexcept>

template <typename T>
double Bisection(double Target,
                 double Low, 
                 double High,
                 double Tolerance,
                 T TheFunction)
{
    if (Low >= High) throw std::invalid_argument("Bisection: Low must be less than High.");
    
    if (TheFunction(Low) > Target) throw std::invalid_argument("Bisection: TheFunction(Low) must be below Target.");

    if (TheFunction(High) < Target) throw std::invalid_argument("Bisection: TheFunction(High) must be above Target.");

    if (Tolerance <= 0.0)
        throw std::invalid_argument("Bisection: Tolerance must be positive.");
    double x = 0.5 * (Low + High);
    double y = TheFunction(x);

    static const int MAX_ITER = 1000;
    int iter = 0;
    do 
    {
        if (y < Target)
        {
            Low = x;
        }
        
        if (y > Target)
        {
            High = x;
        }
        
        x = 0.5 * (Low + High);
        y = TheFunction(x);
        iter++;
        if (iter > MAX_ITER)
            throw std::runtime_error("Bisection: Maximum iterations exceeded. Bisection may not converge.");
    }
    while(std::abs(y-Target) > Tolerance);

    return x;
}