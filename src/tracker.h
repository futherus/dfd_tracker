#ifndef TRACKER_H
#define TRACKER_H

#include <utility>
#include <fmt/format.h>
#include "debug.h"
#include "gviz_printer.h"

#define FLF_ARGS const char* file__ = "", int line__ = 0, const char* func__ = ""
#define FLF_STR fmt::format("{}:{} {}", file__, line__, func__).data()

namespace tr
{

class Tracker
{
private:
    int value_;

    std::string name_;
    std::string last_id_;

public:
    // std::string getId() { return last_id_; }

    Tracker(int value,
            const char* var__ = "Anon",
            FLF_ARGS)
        : value_(value)
        , name_(var__)
        , last_id_("No ID")
    {
        $M("%s %s::%s\n", FLF_STR, name_.data(), "{Constructor}");

        gviz::Printer& printer = gviz::Printer::instance();

        gviz::VariableNode node(name_, std::to_string(value_));
        last_id_ = printer.node(node);
    }

    Tracker(const Tracker& that,
            const char* var__ = "Anon",
            FLF_ARGS)
        : value_(that.value_)
        , name_(var__)
        , last_id_("No ID")
    {
        $M("%s %s::%s\n", FLF_STR, name_.data(), "{Copy constructor}");

        gviz::Printer& printer = gviz::Printer::instance();

        gviz::VariableNode node(name_);
        last_id_ = printer.node(node);

        printer.edge(that.last_id_, last_id_);
    }

    Tracker(Tracker&& that,
            const char* var__ = "Anon",
            FLF_ARGS)
        : value_(std::exchange(that.value_, 0))
        , name_(var__)
        , last_id_("No ID")
    {
        $M("%s %s::%s\n", FLF_STR, name_.data(), "{Move constructor}");

        gviz::Printer& printer = gviz::Printer::instance();

        gviz::VariableNode node(name_);
        last_id_ = printer.node(node);

        printer.edge(that.last_id_, last_id_);
    }

    ~Tracker()
    {
        $M("%s::{Destructor}\n", name_.data());
    }

    Tracker& operator=(const Tracker& that)
    {
        $M("%s::{Copy assignment}\n", name_.data());
        value_ = that.value_;

        gviz::Printer& printer = gviz::Printer::instance();

        gviz::BinaryNode op_node("*" + name_, "=", "const&" + that.name_); 
        std::string op = printer.node(op_node);

        printer.edge(last_id_, op + ":lhs");
        printer.edge(that.last_id_, op + ":rhs");

        gviz::VariableNode var_node(name_);
        last_id_ = printer.node(var_node);
        printer.edge(op + ":res", last_id_);

        return *this;
    }

    Tracker& operator=(Tracker&& that)
    {
        $M("%s::{Move assignment}\n", name_.data());
        std::swap(value_, that.value_);

        return *this;
    }

    Tracker& operator+=(const Tracker& rhs)
    {
        $M("%s::{operator+=}\n", name_.data());
        value_ += rhs.value_;

        return *this;
    }

    Tracker& operator-=(const Tracker& rhs)
    {
        $M("%s::{operator-=}\n", name_.data());
        value_ -= rhs.value_;

        return *this;
    }
};

Tracker operator+(Tracker lhs, const Tracker& rhs);
Tracker operator-(Tracker lhs, const Tracker& rhs);

} // namespace tr

#define Tracker(VAR, VAL) tr::Tracker VAR(VAL, #VAR, __FILE__, __LINE__, __PRETTY_FUNCTION__)

// template <const char* FILE__, int LINE__>
// class Test
// {
// private:

// public:
//     Test()
//     {
//         std::printf("%s:%d\n", FILE__, LINE__);
//     }
// };

// #define Test Test<FILE_NAME, __LINE__>

#endif // TRACKER_H
