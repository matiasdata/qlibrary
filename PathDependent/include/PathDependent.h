#include <MyArray.h>
#include <vector>

class CashFlow
{
public:    
    CashFlow(unsigned long TimeIndex_ = 0UL, double Amount_ = 0.0) : TimeIndex{TimeIndex_}, Amount{Amount_} {};
    unsigned long TimeIndex;
    double Amount;
};

class PathDependent
{
public:
    PathDependent(MyArray& LookAtTimes_);
    const MyArray& GetLookAtTimes() const;
    virtual unsigned long MaxNumberOfCashFlows() const = 0;
    virtual MyArray PossibleCashFlowTimes() const = 0;
    virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const = 0;
    virtual PathDependent* clone() const = 0;
    virtual ~PathDependent(){};
private:
    MyArray LookAtTimes;
};