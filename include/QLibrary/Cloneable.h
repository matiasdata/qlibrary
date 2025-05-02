#pragma once

namespace QLibrary{

template <typename Base, typename Derived>
class Cloneable : public Base
{
public:
    Base* clone() const override {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

}// namespace QLibrary

/*
static_cast<const Derived&>(*this) safely downcasts the current object from Cloneable<Base, Derived> to Derived 
because CRTP guarantees that this is safe (you control both base and derived).

new Derived(*this) won't work because *this has type const Cloneable<Base, Derived>& and
Derived has no constructor taking a Cloneable<Base, Derived>, so you'd get a compiler error — unless you cast it properly.
*/