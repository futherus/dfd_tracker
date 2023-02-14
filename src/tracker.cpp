#include "tracker.h"

Tracker operator+(Tracker lhs, const Tracker& rhs)
{$$
    return lhs += rhs;
}

Tracker operator-(Tracker lhs, const Tracker& rhs)
{$$
    return lhs -= rhs;
}
