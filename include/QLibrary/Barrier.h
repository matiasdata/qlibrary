// Barrier.h
#pragma once
#include <QLibrary/MyArray.h>
#include <QLibrary/PathDependent.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>
#include <optional>

namespace QLibrary{

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
    UpOutBarrier(double level_, double rebate_ = 0.0) : level(level_), rebate(rebate_) {};
    virtual std::optional<CashFlow> evaluate(const MyArray& SpotValues, const Wrapper<Payoff>& payoff) const override;
    virtual Barrier* clone() const override;
private:
    double level;
    double rebate;
};

class UpInBarrier : public Barrier {
    public:
        UpInBarrier(double level_, double rebate_ = 0.0): level(level_), rebate(rebate_) {};
        virtual std::optional<CashFlow> evaluate(const MyArray& SpotValues, const Wrapper<Payoff>& payoff) const override;
        virtual Barrier* clone() const override;
    private:
        double level;
        double rebate;
    };

} // namespace QLibrary