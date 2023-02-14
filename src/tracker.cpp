#include "tracker.h"

namespace tr
{

Tracker operator+(Tracker lhs, const Tracker& rhs)
{$$
    return lhs += rhs;
}

Tracker operator-(Tracker lhs, const Tracker& rhs)
{$$
    return lhs -= rhs;
}

} // namespace tr
