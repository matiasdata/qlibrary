#include <Payoff1.h>
#include <algorithm>
#include <stdexcept>


Payoff::Payoff(double Strike_, OptionType TheOptionType_) : Strike{Strike_}, TheOptionType{TheOptionType_} {};

double Payoff::operator()(double Spot) const
{
    switch(TheOptionType)
    {
    case call : return std::max(Spot-Strike,0.0);
    case put : return std::max(Strike-Spot,0.0);
    default: throw std::runtime_error{"unknown option type found."};
    }
}

/* In order to use #include <Payoff1.h> instead of #include "Payoff1.h" one need to ensure that the compiler can find 
the Payoff1.h file in its system-wide include directories, rather than just searching the local project directory 
where the file may be located. We compile the program with the commands:
g++ -std=c++20 -I./include -c main.cpp -o main.o
g++ main.o -o main
*/

/* Switch statements are not nice, and they usually showcase a problem in the design of the code. Not only because they will slow down code.
*/
