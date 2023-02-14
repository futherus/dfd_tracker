#ifndef GVIZ_PRINTER_H
#define GVIZ_PRINTER_H

#include <iostream>
#include <assert.h>
#include <fstream>
#include <fmt/format.h>
#include <memory>

namespace gviz
{

class Node
{
public:
    virtual std::string toString() = 0;
};

class VariableNode : public Node
{
private:
    std::string name_;
    std::string initializer_;

public:
    VariableNode(const std::string& name,
                 const std::string& initializer = "")
        : name_(name)
        , initializer_(initializer)
    {}

    std::string toString() override
    {
        std::string str = fmt::format("shape=box,"
                                      "label=\"{}",
                                      name_);
        if (!initializer_.empty())
            str += fmt::format("{{{}}}", initializer_);

        str += "\"";

        return str;
    }
};

class BinaryNode : public Node
{
private:
    std::string lhs_;
    std::string op_;
    std::string rhs_;

public:
    BinaryNode(const std::string& lhs,
               const std::string& op,
               const std::string& rhs)
        : lhs_(lhs)
        , op_(op)
        , rhs_(rhs)
    {}

    std::string toString() override
    {
        return fmt::format("shape=record,"
                           "label=\"{{ {{<lhs> {} | {} | <rhs> {} }} | <res> res }}\"", 
                           lhs_, op_, rhs_);
    }
};

class Printer
{
private:
    std::ofstream ostr_;

    size_t cur_id_;

    static std::unique_ptr<Printer> instance_;

    Printer(std::string filename)
        : ostr_(filename)
        , cur_id_(0)
    {
        ostr_ << "digraph G {\n";
    }

public:
    ~Printer()
    {
        ostr_ << "}\n";
    }

    static void init(std::string filename)
    {
        assert(instance_.get() == nullptr && "Already initialized");

        instance_.reset(new Printer(filename));
    }

    static Printer& instance()
    {
        assert(instance_.get() && "Not initialized");

        return *instance_;
    }

    std::string getUniqueId()
    {
        return fmt::format("node_{}", cur_id_++);
    }

    void edge(std::string fromId, std::string toId)
    {
        ostr_ << "\t" << fromId << " -> " << toId << std::endl;
    }

    std::string node(Node& node)
    {
        std::string id = getUniqueId();
        ostr_ << "\t" << id << "[" << node.toString() << "]\n";

        return id;
    }
};

}

#endif // GVIZ_PRINTER_H
