// PathDependentAsian.h
#include <QLibrary/PathDependent.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>

class PathDependentAsian : public PathDependent
{
public:
    PathDependentAsian(const MyArray& LookAtTimes_, double DeliveryTime_, const Wrapper<Payoff>& ThePayoff_);
    virtual unsigned long MaxNumberOfCashFlows() const override;
    virtual MyArray PossibleCashFlowTimes() const override;
    virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const override;
    virtual ~PathDependentAsian() override = default;
    virtual PathDependent* clone() const override;
private:
    double DeliveryTime;
    Wrapper<Payoff> ThePayoff;
    unsigned long NumberOfTimes;
};