#include <PathDependent.h>

PathDependent::PathDependent(MyArray& LookAtTimes_) : LookAtTimes{LookAtTimes_} {}

const MyArray& PathDependent::GetLookAtTimes() const {return LookAtTimes;}
