// PathDependent.cpp
#include <QLibrary/PathDependent.h>

namespace QLibrary{

PathDependent::PathDependent(const MyArray& LookAtTimes_) : LookAtTimes{LookAtTimes_} {}

const MyArray& PathDependent::GetLookAtTimes() const {return LookAtTimes;}

}
