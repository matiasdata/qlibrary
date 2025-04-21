#pragma once
#include <QLibrary/MyArray.h>
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
    PathDependent(const MyArray& LookAtTimes_);
    const MyArray& GetLookAtTimes() const;
    virtual unsigned long MaxNumberOfCashFlows() const = 0;
    virtual MyArray PossibleCashFlowTimes() const = 0;
    virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const = 0;
    virtual PathDependent* clone() const = 0;
    virtual ~PathDependent(){};
private:
    MyArray LookAtTimes;
};

/*
PathDependent is a virtual base class for PathDependent Exotic (but European) options.

LookAtTimes is an array that stores all times where the option can Look at the Spot value.

const MyArray& GetLookAtTimes() const: returns the LookAtTimes array but being const it can't be modified.

virtual unsigned long MaxNumberOfCashFlows() const = 0: (virtual) returns the maximum number of CashFlows that the option can have.

virtual MyArray PossibleCashFlowTimes() const = 0: (virtual) returns the possible CashFlow times (i.e. when cashflows can happen) in an array.

virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const = 0:
    Computes the CashFlows of the options using the SpotValues given and stores these in the GeneratedCashFlows.
    Returns the size (length) of the CashFlows.
*/