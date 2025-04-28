// PathDependentBarrier.h
#include <QLibrary/PathDependent.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Barrier.h>
#include <QLibrary/Wrapper.h>

namespace QLibrary{

class PathDependentBarrier : public PathDependent
{
public:
    PathDependentBarrier(const MyArray& LookAtTimes_, const Wrapper<Payoff>& ThePayoff_, const Wrapper<Barrier>& TheBarrier_);
    virtual unsigned long MaxNumberOfCashFlows() const override;
    virtual MyArray PossibleCashFlowTimes() const override;
    virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const override;
    virtual ~PathDependentBarrier() override = default;
    virtual PathDependent* clone() const override;
private:
    Wrapper<Payoff> ThePayoff;
    Wrapper<Barrier> TheBarrier;
    unsigned long NumberOfTimes;
};
}