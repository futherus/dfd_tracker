#include <utility>
#include "debug.h"

class Tracker
{
private:
    int value_;

public:
    Tracker(int value)
        : value_(value)
    {$$}

    Tracker(const Tracker& that)
        : value_(that.value_)
    {$$}

    Tracker(Tracker&& that)
        : value_(std::exchange(that.value_, 0))
    {$$}

    Tracker& operator=(const Tracker& that)
    {$$
        value_ = that.value_;

        return *this;
    }

    Tracker& operator=(Tracker&& that)
    {$$
        std::swap(value_, that.value_);

        return *this;
    }

    ~Tracker() {$$}

    Tracker& operator+=(const Tracker& rhs)
    {$$
        value_ += rhs.value_;

        return *this;
    }

    Tracker& operator-=(const Tracker& rhs)
    {$$
        value_ -= rhs.value_;

        return *this;
    }
};

Tracker operator+(Tracker lhs, const Tracker& rhs);
Tracker operator-(Tracker lhs, const Tracker& rhs);
