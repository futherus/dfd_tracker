#include "tracker.h"
#include <fmt/format.h>
#include "gviz_printer.h"

int main()
{
    gviz::Printer::init("test.dot");

    Tracker(x, 5);

    Tracker(y, 6);

    y = x;


    // Test x;

    return 0;
}