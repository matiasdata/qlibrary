// TestTree/main.cpp

#include <QLibrary/TreeAmerican.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>
#include <iostream>

int main()
{
    double Strike = 100.0;
    double FinalTime = 1.0;
    QLibrary::PayoffCall ThePayoff(Strike);
    QLibrary::TreeAmerican TheTree(FinalTime,ThePayoff);
    std::cout << TheTree.PreFinalValue(120,0.5,121.5) << std::endl;

    return 0;
}
