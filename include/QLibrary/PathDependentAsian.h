// PathDependentAsian.h
#include <QLibrary/PathDependent.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>

class PathDependentAsian : public PathDependent
{
public:
    PathDependentAsian(const MyArray& LookAtTimes_, double DeliveryTime_, const Wrapper<Payoff>& ThePayoff_);
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MyArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const;
    virtual ~PathDependentAsian(){};
    virtual PathDependent* clone() const;
private:
    double DeliveryTime;
    Wrapper<Payoff> ThePayoff;
    unsigned long NumberOfTimes;
};