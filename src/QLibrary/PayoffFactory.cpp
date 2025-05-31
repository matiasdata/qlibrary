// PayoffFactory.cpp

#include <QLibrary/PayoffFactory.h>
#include <iostream>

namespace QLibrary
{

void PayoffFactory::RegisterPayoff(std::string PayoffId, CreatePayoffFunction CreatorFunction)
{
    TheCreatorFunctions.insert(std::pair<std::string, CreatePayoffFunction>(PayoffId, CreatorFunction));
}

Payoff* PayoffFactory::CreatePayoff(std::string PayoffId, const std::vector<double>& Parameters)
{
    std::map<std::string,CreatePayoffFunction>::const_iterator i = TheCreatorFunctions.find(PayoffId); 
    // can use auto for readability later, but in this case we declare the iterator explicitely.
    if (i == TheCreatorFunctions.end())
    {
        std::cout << PayoffId << " is an unknown payoff." << std::endl;
        return nullptr;
    }
    return (i->second)(Parameters);
}

PayoffFactory& PayoffFactory::Instance()
{
    static PayoffFactory theFactory;
    return theFactory;
}

} // namespace QLibrary