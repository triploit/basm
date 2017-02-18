#ifndef HLT_HPP
#define HLT_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Hlt : public Command
{
private:
    std::regex name = std::regex("^((H|h)(L|l)(T|t))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            exit(0);

        Compiler.addLine("exit(0);");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
