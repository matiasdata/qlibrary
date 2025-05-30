#include <iostream>
#include <SimpleMC.h>
#include <Vanilla.h>
#include <Parameters.h>

int main()
{
    double Strike = 100;
    std::cout << "Strike: " << Strike <<std::endl;
    double Spot = 120;
    std::cout << "Spot: " << Spot <<std::endl;
    PayoffCall callPayoff(Strike); // notice how the enum inside the class is called, so that we can create a call or put option.
    PayoffPut putPayoff(Strike);
    double Lower = 100;
    double Upper = 120;
    PayoffDoubleDigital doubleDigitalPayoff(Lower,Upper);
    std::cout << "Call Payoff: " << callPayoff(Spot) << std::endl;
    std::cout << "Put Payoff: " << putPayoff(Spot) << std::endl;
    Spot = 100;
    std::cout << "Spot: " << Spot <<std::endl;
    parametersConstant Vol{0.2};
    parametersPiecewise Vol2({0.0, 0.5, 1.0}, {0.4, 0.3, 0.2});
    parametersConstant r{0.05};
    parametersPiecewise r2({0.0, 0.5, 1.0}, {0.05, 0.04, 0.03});
    // std::cout << "Realized Variance: " << Vol2.IntegralSquare(0,1) << std::endl;
    double Expiry = 1;
    unsigned long NumberOfPaths = 1000000;
    VanillaOption callOption(callPayoff,Expiry);
    VanillaOption putOption(putPayoff,Expiry);
    VanillaOption doubleDigitalOption(doubleDigitalPayoff,Expiry);
    // Print MC simulation results
    std::cout << "Monte Carlo price of a call: " << SimpleMonteCarlo(callOption, Spot, Vol2, r2, NumberOfPaths) << std::endl;
    std::cout << "Monte Carlo price of a put: " << SimpleMonteCarlo(putOption, Spot, Vol2, r2, NumberOfPaths) << std::endl;
    std::cout << "Monte Carlo price of a double digital: " << SimpleMonteCarlo(doubleDigitalOption, Spot, Vol2, r2, NumberOfPaths) << std::endl;
    return 0;
}

