#include <Payoff1.h>
#include <iostream>
#include <SimpleMC.h>

int main()
{
    double Strike = 100;
    std::cout << "Strike: " << Strike <<std::endl;
    double Spot = 120;
    std::cout << "Spot: " << Spot <<std::endl;
    Payoff callPayoff(Strike,Payoff::call); // notice how the enum inside the class is called, so that we can create a call or put option.
    Payoff putPayoff(Strike,Payoff::put);
    std::cout << "Call Payoff: " << callPayoff(Spot) << std::endl;
    std::cout << "Put Payoff: " << putPayoff(Spot) << std::endl;
    Spot = 100;
    std::cout << "Spot: " << Spot <<std::endl;
    double Vol = 0.2;
    double r = 0.05;
    double Expiry = 1;
    unsigned long NumberOfPaths = 1000000;
    // Print MC simulation results
    std::cout << "Monte Carlo price of a call: " << SimpleMonteCarlo(callPayoff,Expiry,Spot,Vol,r,NumberOfPaths) << std::endl;
    std::cout << "Monte Carlo price of a put: " << SimpleMonteCarlo(putPayoff,Expiry,Spot,Vol,r,NumberOfPaths) << std::endl;
    return 0;
}