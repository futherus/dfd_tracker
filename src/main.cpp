#include "tracker.h"

int main()
{
    Tracker x{5};
    Tracker y{5};

    Tracker z{x + y};

    return 0;
}