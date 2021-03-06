#ifndef POP_HPP
#define POP_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Pop : public Command
{
private:
    std::regex name = std::regex("^((P|p)(O|o)(P|p))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            Runtime.popStack();

        Compiler.addLine("stack.pop();");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
