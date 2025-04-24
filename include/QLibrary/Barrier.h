// Barrier.h
#pragma once
#include <QLibrary/MyArray.h>
#include <QLibrary/PathDependent.h>
#include <optional>

class Barrier
{
public:
    Barrier(){};
    virtual std::optional<CashFlow> evaluate(const MyArray& SpotValues, const Wrapper<Payoff>& ThePayoff) const = 0;
    virtual Barrier* clone() const = 0;
    virtual ~Barrier() = default;
};

class UpOutBarrier : public Barrier {
public:
    UpOutBarrier(double level_, double rebate_);
    virtual std::optional<CashFlow> evaluate(const MyArray& SpotValues, const Wrapper<Payoff>& payoff) const override;
    virtual Barrier* clone() const override;
private:
    double level;
    double rebate;
};