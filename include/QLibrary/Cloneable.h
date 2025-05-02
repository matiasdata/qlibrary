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
 Cloneable Curiously recurring template pattern (CRTP) for Clone.

This template enables automatic deep-copy polymorphism via the clone() method, using the Curiously Recurring Template Pattern (CRTP).

Usage:
1. Your abstract base class should declare:

    virtual Base* clone() const = 0;

2. Your derived class should inherit as:

    class Derived : public Cloneable<Base, Derived> { ... };

   (Do NOT reimplement `clone()` in Derived — it is inherited.)

3. This enables:

    Base* b1 = new Derived(...);
    Base* b2 = b1->clone();  // deep copy as Derived

Implementation:

Cloneable<Base, Derived> provides:

Base* clone() const override {
    return new Derived(static_cast<const Derived&>(*this));
}

This uses CRTP to safely downcast and copy the derived class
without requiring boilerplate clone() implementations in every subclass.
new Derived(*this) won't work because *this has type const Cloneable<Base, Derived>& and
Derived has no constructor taking a Cloneable<Base, Derived>, so you'd get a compiler error — unless you cast it properly.

Notes:
- The base class must have a virtual destructor.
- The derived class must have a public copy constructor.
*/