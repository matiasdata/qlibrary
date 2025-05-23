#include <Payoff.h>
#include <iostream>
#include <SimpleMC.h>
#include <Vanilla.h>

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
    double Vol = 0.2;
    double r = 0.05;
    double Expiry = 1;
    unsigned long NumberOfPaths = 1000000;
    VanillaOption callOption(callPayoff,Expiry);
    VanillaOption putOption(putPayoff,Expiry);
    VanillaOption doubleDigitalOption(doubleDigitalPayoff,Expiry);
    // Print MC simulation results
    std::cout << "Monte Carlo price of a call: " << SimpleMonteCarlo(callOption,Spot,Vol,r,NumberOfPaths) << std::endl;
    std::cout << "Monte Carlo price of a put: " << SimpleMonteCarlo(putOption,Spot,Vol,r,NumberOfPaths) << std::endl;
    std::cout << "Monte Carlo price of a double digital: " << SimpleMonteCarlo(doubleDigitalOption,Spot,Vol,r,NumberOfPaths) << std::endl;
    return 0;
}

/* Notice that the line 
VanillaOption callOption(callPayoff,Expiry);  
compiles without error, even thou the VanillaOption constructor requires a PayoffBridge object.
The reason is that there is a constructor for PayOffBridge which takes in an object of
type PayOff&. The compiler automatically accepts the inherited class object as
a substitute for the base class object, and then silently converts it for us into the
PayoffBridge object which is then passed to the VanillaOption constructor.
*/