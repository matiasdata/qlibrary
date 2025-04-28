// Parameters.cpp
#include <QLibrary/Parameters.h>

// parametersConstant class
namespace QLibrary{

parametersConstant::parametersConstant(double Constant_) : Constant{Constant_} {}
// Constructor for parametersConstant class

Parameters* parametersConstant::clone() const
{
    return new parametersConstant(*this); // clone function for parametersConstant class
}
// This function creates a new object of type parametersConstant and returns a pointer to it.

double parametersConstant::Integral(double Time1, double Time2) const
{
    return Constant * (Time2 - Time1); // integral of a constant function
}

double parametersConstant::IntegralSquare(double Time1, double Time2) const
{
    return Constant * Constant * (Time2 - Time1); // integral of a constant function squared
}
// The Integral function calculates the integral of a constant function over the interval [Time1, Time2].


// parametersPiecewise class

parametersPiecewise::parametersPiecewise(const std::vector<double>& Time_, const std::vector<double>& Value_)
{
    if (Time_.size() != Value_.size()) {
        throw std::invalid_argument("Time and Value vectors must have the same size."); // check if the size of Time and Value vectors are equal
    }
    for (size_t i = 0; i < Time_.size() - 1; ++i)
    {
        if (Time_[i] >= Time_[i+1]) {
            throw std::invalid_argument("Time vector must be strictly increasing."); // check if the Time vector is strictly increasing
        }
    }
    Time = Time_; // initialize the Time  (performs deep copy)
    Value = Value_; // initialize the Value vector (performs deep copy)
}
// Constructor for parametersPiecewise class
// It takes two vectors as input: Time_ and Value_. It checks if the size of both vectors is equal and if the Time vector is strictly increasing.
// If the checks pass, it initializes the Time and Value vectors with the input values.


Parameters* parametersPiecewise::clone() const
{
    return new parametersPiecewise(*this); // clone function for parametersPiecewise class
}
// This function creates a new object of type parametersPiecewise and returns a pointer to it.


double parametersPiecewise::Integral(double Time1, double Time2) const
{
    double result = 0.0;
    // Iterate over the piecewise intervals
    for (size_t i = 0; i < Time.size() - 1; ++i)
    {
        // Check if the interval overlaps with the integration range [Time1, Time2]
        double t1 = std::max(Time1, Time[i]);      // Start of the integration interval
        double t2 = std::min(Time2, Time[i + 1]);  // End of the integration interval
        if (t1 < t2)  // If the interval [t1, t2] is valid
        {
            result += Value[i] * (t2 - t1);  // Perform integration
        }
    }
    return result;
}

double parametersPiecewise::IntegralSquare(double Time1, double Time2) const
{
    double result = 0.0;
    // Iterate over the piecewise intervals
    for (size_t i = 0; i < Time.size() - 1; ++i)
    {
        // Check if the interval overlaps with the integration range [Time1, Time2]
        double t1 = std::max(Time1, Time[i]);      // Start of the integration interval
        double t2 = std::min(Time2, Time[i + 1]);  // End of the integration interval
        if (t1 < t2)  // If the interval [t1, t2] is valid
        {
            result += Value[i] * Value[i] * (t2 - t1);  // Perform integration
        }
    }
    return result;
}

}