// PathDependent.cpp
#include <QLibrary/PathDependent.h>

PathDependent::PathDependent(const MyArray& LookAtTimes_) : LookAtTimes{LookAtTimes_} {}

const MyArray& PathDependent::GetLookAtTimes() const {return LookAtTimes;}
