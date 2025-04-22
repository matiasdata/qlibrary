// PathDependentDiscreteKnockout.h
#include <QLibrary/PathDependent.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>

class PathDependentDiscreteKnockout : public PathDependent
{
public:
    PathDependentDiscreteKnockout(const MyArray& LookAtTimes_, const Wrapper<Payoff>& ThePayoff_);
    virtual unsigned long MaxNumberOfCashFlows() const override;
    virtual MyArray PossibleCashFlowTimes() const override;
    virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const override;
    virtual ~PathDependentDiscreteKnockout() override = default;
    virtual PathDependent* clone() const override;
private:
    Wrapper<Payoff> ThePayoff;
};