#pragma once
#include <QLibrary/MyArray.h>
#include <optional>

class Barrier
{
public:
    Barrier(){};
    std::optional<unsigned long> operator()(const MyArray& SpotValues) const;
    virtual bool checkOnce(double Spot) const = 0;
    virtual Barrier* clone() const = 0;
    virtual ~Barrier(){};
private:
};

class UpOutBarrier : Barrier
{
public:
    UpOutBarrier(double Barrier_);
    virtual bool checkOnce(double Spot) const override;
    virtual Barrier* clone() const override;
    virtual ~UpOutBarrier() override = default;
private:
    double Barrier;
};